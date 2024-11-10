# 🌱 Smart Plant Watering Project

![Plant Watering](images/plant_watering_banner.jpg)

This **Smart Plant Watering Project** is an automated solution to monitor and maintain soil moisture for your plants. Using a NodeMCU ESP8266 connected to the Blynk IoT platform, soil moisture and temperature/humidity sensors, OLED display, and water pump relay, this project ensures your plants get the right amount of water when needed.

---

## 📋 Table of Contents

- [✨ Features](#features)
- [🔧 Hardware Requirements](#hardware-requirements)
- [💻 Software Requirements](#software-requirements)
- [📑 Setup Instructions](#setup-instructions)
- [🚀 Usage](#usage)
- [📜 Code Description](#code-description)
- [📄 License](#license)

---

## ✨ Features

- **Automatic Soil Moisture Monitoring**: Automatically waters plants when soil moisture drops below a set threshold.
- **Temperature and Humidity Monitoring**: Measures environmental temperature and humidity.
- **Remote Control and Monitoring**: Monitor and control settings from the Blynk app.
- **Manual Pump Override**: Turn the pump on/off manually from the Blynk app.
- **OLED Display**: Real-time display of soil moisture, temperature, and humidity.
- **EEPROM Storage**: Saves soil moisture threshold settings to EEPROM.

---

## 🔧 Hardware Requirements

![Hardware Setup](images/hardware_setup.png)

- **ESP8266 NodeMCU** (ESP-12E)
- **Soil Moisture Sensor**
- **DHT11 Temperature and Humidity Sensor**
- **Relay Module**
- **Water Pump**
- **OLED Display (128x64)**
- **Power Supply**

---

## 💻 Software Requirements

- **Arduino IDE**
- **Blynk IoT App** (available on iOS & Android)
- **Libraries**:
  - [Blynk Library](https://github.com/blynkkk/blynk-library) (`BlynkSimpleEsp8266.h`)
  - [Adafruit GFX and SSD1306 Libraries](https://github.com/adafruit/Adafruit-GFX-Library) for OLED display
  - [DHTesp Library](https://github.com/beegee-tokyo/DHTesp) for the DHT11 sensor

---

## 📑 Setup Instructions

### 1️⃣ Hardware Setup

- Connect the **Soil Moisture Sensor** to analog pin (`A0`) of the NodeMCU.
- Connect the **Relay Module** to pin `D7` (GPIO13).
- Connect the **DHT11 Sensor** to pin `D2` (GPIO4).
- Connect the **OLED Display** to the I2C pins (`SDA` and `SCL`).
- Connect the **Water Pump** to the relay.

### 2️⃣ Blynk Setup

1. Download the [Blynk app](https://blynk.io) and create a new project.
2. Enter the **Template ID**, **Template Name**, and **Auth Token** from the code in your project.
3. Add the following virtual pins:
   - `V1` for soil moisture
   - `V2` for temperature
   - `V3` for humidity
   - `V4` for manual pump override
   - `V5` for setting moisture threshold

### 3️⃣ Arduino Code Setup

- Open the code in **Arduino IDE**.
- Update the **Wi-Fi credentials** in the code:
  ```cpp
  char ssid[] = "your_network_ssid";
  char pass[] = "your_network_password";

Enter your Blynk Auth Token:

char auth[] = "your_blynk_auth_token";

Upload the code to your ESP8266.



---

🚀 Usage

Monitor real-time soil moisture, temperature, and humidity from the Blynk app.

Use Manual Pump Control to override automatic watering as needed.

Adjust the Soil Moisture Threshold from the app; this threshold will be saved to EEPROM to retain settings after reboot.



---

📜 Code Description

Key Components

Sensor Data Collection: Reads soil moisture (analog input) and environmental data from the DHT11 sensor.

Pump Control: The pump activates when the soil moisture is below the threshold and automatically deactivates after a specified duration.

Error Handling: Displays errors on the OLED display if sensors are disconnected or return invalid values.

Blynk Integration: Sends sensor data to Blynk for remote monitoring and receives commands from the app for manual pump control.

EEPROM Storage: Stores and retrieves the soil moisture threshold, avoiding the need to reset it on every restart.


Main Functions

sendSensorData(): Reads sensor data, sends it to the Blynk app, displays it on the OLED, and manages the pump state.

managePump(): Controls the pump based on moisture levels and timeout conditions.

startPump() and stopPump(): Turn the pump on/off and update the Blynk app and internal states.

checkConnection(): Ensures Wi-Fi and Blynk connectivity, attempting reconnection if needed.

loadThresholdFromEEPROM() and saveThresholdToEEPROM(): Manage EEPROM storage for moisture thresholds.



---

📄 License

This project is open-source and free to use.


---

This Smart Plant Watering Project helps keep your plants healthy by ensuring they receive the right amount of water, and allows you to monitor environmental conditions remotely. Perfect for plant enthusiasts, busy plant parents, or anyone interested in IoT!

Happy Gardening! 🌿
