#define BLYNK_TEMPLATE_ID "TMPL6gubuUsA2"
#define BLYNK_TEMPLATE_NAME "SMART PLANT WATERING PROJECT"
#define BLYNK_AUTH_TOKEN "v5kze5bCMFfgM1pYNdTDEKOz6IZvCFyS"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHTesp.h>
#include <EEPROM.h>

// Display configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pin definitions
#define SOIL_MOISTURE_PIN A0
#define RELAY_PIN 13
#define DHTPIN D4

// Network credentials
char ssid[] = "iot"; 
char pass[] = "12345678"; 
char auth[] = BLYNK_AUTH_TOKEN;

// System states and timings
BlynkTimer timer;
bool pumpState = false;
bool manualOverride = false;
bool wateringInProgress = false;

// Timing constants
const unsigned long PUMP_RUN_TIME = 10000;  // 10 seconds
const unsigned long RECONNECT_INTERVAL = 30000;  // 30 seconds
const unsigned long MOISTURE_STABILIZATION_DELAY = 5000;  // 5 seconds
const unsigned long SAFETY_TIMEOUT = 60000;  // 1 minute maximum pump run time
const unsigned long WIFI_TIMEOUT = 20000;  // 20 seconds WiFi connection timeout
const uint8_t MAX_RECONNECT_ATTEMPTS = 5;  // Maximum reconnection attempts

// Soil moisture calibration values
const int MOISTURE_AIR_VALUE = 1023;    // Value in air
const int MOISTURE_WATER_VALUE = 0;     // Value in water
const int MOISTURE_READINGS = 5;        // Number of readings to average

// Sensor readings and thresholds
struct SystemState {
  int soilMoisture;
  float temperature;
  float humidity;
  int moistureThreshold;
  unsigned long lastWateringTime;
  uint8_t reconnectAttempts;
} state;

// Timing variables
unsigned long pumpStartTime = 0;
unsigned long lastReconnectAttempt = 0;
unsigned long lastWateringCheck = 0;

DHTesp dht;

// Function declarations (prototypes)
bool hasTimeElapsed(unsigned long start, unsigned long interval);
void saveThresholdToEEPROM();
void loadThresholdFromEEPROM();
void checkConnection();
int readSoilMoisture();
void sendSensorData();
void managePump();
void startPump();
void stopPump();
void displayData();
void displayError(const __FlashStringHelper* errorMsg);

// Function implementations
bool hasTimeElapsed(unsigned long start, unsigned long interval) {
    unsigned long currentTime = millis();
    return (currentTime - start) >= interval;
}

void saveThresholdToEEPROM() {
    if (state.moistureThreshold >= 0 && state.moistureThreshold <= 100) {
        EEPROM.begin(512);
        EEPROM.put(0, state.moistureThreshold);
        boolean success = EEPROM.commit();
        if (!success) {
            displayError(F("EEPROM write failed"));
        }
    }
}

void loadThresholdFromEEPROM() {
    EEPROM.begin(512);
    EEPROM.get(0, state.moistureThreshold);
    if (state.moistureThreshold < 0 || state.moistureThreshold > 100) {
        state.moistureThreshold = 30;  // Default if EEPROM value is invalid
        saveThresholdToEEPROM();
    }
}

void checkConnection() {
    if (WiFi.status() != WL_CONNECTED || !Blynk.connected()) {
        if (state.reconnectAttempts >= MAX_RECONNECT_ATTEMPTS) {
            displayError(F("Max reconnect attempts reached"));
            ESP.restart();  // Reset device after max attempts
            return;
        }

        if (hasTimeElapsed(lastReconnectAttempt, RECONNECT_INTERVAL)) {
            lastReconnectAttempt = millis();
            state.reconnectAttempts++;
            
            Serial.println(F("Attempting to reconnect..."));
            WiFi.disconnect();
            WiFi.begin(ssid, pass);
            
            // Wait for connection with timeout
            unsigned long startAttempt = millis();
            while (WiFi.status() != WL_CONNECTED) {
                if (hasTimeElapsed(startAttempt, WIFI_TIMEOUT)) {
                    displayError(F("WiFi timeout"));
                    return;
                }
                delay(500);
            }
            
            if (Blynk.connect()) {
                Serial.println(F("Reconnected to Blynk!"));
                state.reconnectAttempts = 0;  // Reset counter on successful connection
            }
        }
    }
}

int readSoilMoisture() {
    long sum = 0;
    for (int i = 0; i < MOISTURE_READINGS; i++) {
        sum += analogRead(SOIL_MOISTURE_PIN);
        delay(50);  // Short delay between readings
    }
    int rawMoisture = sum / MOISTURE_READINGS;
    
    // Check for sensor errors
    if (rawMoisture <= 0 || rawMoisture >= 1023) {
        return -1;  // Error condition
    }
    
    // Map to percentage with calibration values
    return map(rawMoisture, MOISTURE_AIR_VALUE, MOISTURE_WATER_VALUE, 0, 100);
}

void displayError(const __FlashStringHelper* errorMsg) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("ERROR:"));
    display.println(errorMsg);
    display.display();
    
    // Log error to serial
    Serial.print(F("Error: "));
    Serial.println(errorMsg);
}

void displayData() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    
    display.println(F("Plant Monitor"));
    display.println(F("-------------"));
    display.print(F("Moisture: "));
    display.print(state.soilMoisture);
    display.println(F("%"));
    
    display.print(F("Temp: "));
    display.print(state.temperature, 1);  // One decimal place
    display.println(F("C"));
    
    display.print(F("Humid: "));
    display.print(state.humidity, 1);  // One decimal place
    display.println(F("%"));
    
    if (pumpState) {
        display.println(F("Pump: ON"));
    }
    
    display.display();
}

void startPump() {
    digitalWrite(RELAY_PIN, HIGH);
    pumpState = true;
    pumpStartTime = millis();
    wateringInProgress = true;
    Blynk.virtualWrite(V4, 1);
    Serial.println(F("Pump started"));
}

void stopPump() {
    digitalWrite(RELAY_PIN, LOW);
    pumpState = false;
    wateringInProgress = false;
    state.lastWateringTime = millis();
    Blynk.virtualWrite(V4, 0);
    Serial.println(F("Pump stopped"));
}

void managePump() {
    if (manualOverride) {
        return;
    }

    // Check if pump has been running too long (safety check)
    if (pumpState && hasTimeElapsed(pumpStartTime, SAFETY_TIMEOUT)) {
        stopPump();
        displayError(F("Pump timeout!"));
        return;
    }

    // Only check watering needs if not currently watering
    if (!wateringInProgress) {
        if (state.soilMoisture < state.moistureThreshold && 
            hasTimeElapsed(state.lastWateringTime, MOISTURE_STABILIZATION_DELAY)) {
            startPump();
        }
    } else if (pumpState && hasTimeElapsed(pumpStartTime, PUMP_RUN_TIME)) {
        stopPump();
    }
}

void sendSensorData() {
    // Read soil moisture with error checking
    int moistureReading = readSoilMoisture();
    if (moistureReading == -1) {
        displayError(F("Soil sensor error!"));
        return;
    }
    state.soilMoisture = moistureReading;
    
    // Read temperature and humidity with retry
    TempAndHumidity data;
    for (int i = 0; i < 3; i++) {  // Try up to 3 times
        data = dht.getTempAndHumidity();
        if (dht.getStatus() == DHTesp::ERROR_NONE) {
            state.temperature = data.temperature;
            state.humidity = data.humidity;
            break;
        }
        delay(1000);  // Wait before retry
    }
    
    if (dht.getStatus() != DHTesp::ERROR_NONE) {
        displayError(F("DHT sensor error!"));
        return;
    }

    // Send data to Blynk if connected
    if (Blynk.connected()) {
        Blynk.virtualWrite(V1, state.soilMoisture);
        Blynk.virtualWrite(V2, state.temperature);
        Blynk.virtualWrite(V3, state.humidity);
    }

    displayData();
    managePump();
}

// Blynk event handlers
BLYNK_WRITE(V4) {
    manualOverride = param.asInt();
    if (manualOverride) {
        startPump();
    } else {
        stopPump();
    }
}

BLYNK_WRITE(V5) {
    int newThreshold = param.asInt();
    if (newThreshold >= 0 && newThreshold <= 100) {
        state.moistureThreshold = newThreshold;
        saveThresholdToEEPROM();
    }
}

void setup() {
    Serial.begin(115200);
    
    // Initialize display with error handling
    Wire.begin();
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        delay(1000);
        ESP.restart();
    }
    
    // Initialize pins
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);
    pinMode(SOIL_MOISTURE_PIN, INPUT);
    
    // Initialize DHT sensor
    dht.setup(DHTPIN, DHTesp::DHT11);
    
    // Load saved threshold
    loadThresholdFromEEPROM();
    
    // Initialize state
    state.reconnectAttempts = 0;
    state.lastWateringTime = 0;
    
    // Enable watchdog
    ESP.wdtEnable(WDTO_8S);
    
    // Connect to Blynk
    WiFi.begin(ssid, pass);
    Blynk.config(auth);
    
    // Initialize timer
    timer.setInterval(10000L, sendSensorData);
    
    // Initial display
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("System starting..."));
    display.display();
}

void loop() {
    ESP.wdtFeed();  // Feed the watchdog
    checkConnection();
    Blynk.run();
    timer.run();
}
