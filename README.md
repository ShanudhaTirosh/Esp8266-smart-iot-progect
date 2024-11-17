
# 🌱 **Smart Plant Watering System**  

The **Smart Plant Watering System** is an IoT-based solution that automates plant care by monitoring soil moisture, temperature, and humidity, ensuring optimal hydration and health for your plants. It leverages the power of **ESP8266 NodeMCU**, a microcontroller with WiFi capabilities, to integrate with the **Blynk app** for real-time monitoring and remote control.  

---

## 🎯 **Project Goals**  

- Reduce water wastage by automating irrigation.  
- Provide real-time environmental data to enhance plant care.  
- Enable remote control and monitoring through a mobile app.  
- Serve as a learning project for IoT enthusiasts and students.  

---

## 📦 **Components Required**  

### Hardware Components  
- **ESP8266 NodeMCU** – Microcontroller with WiFi capabilities.  
- **DHT11 Sensor** – Measures temperature and humidity.  
- **Soil Moisture Sensor** – Detects soil moisture levels.  
- **OLED Display (SSD1306)** – Displays sensor readings locally.  
- **Relay Module** – Controls the water pump.  
- **Water Pump** – Irrigates the plants.  
- **Jumper Wires** – For wiring connections.  
- **Power Supply** – 5V power adapter or USB source.  

### Optional Components  
- **Water Level Sensor** – To monitor the water reservoir.  
- **Enclosure** – To house the electronics for protection.  

---

## ⚙️ **Key Features**  

- 🌊 **Automatic Plant Watering**: Activates the pump when soil moisture falls below the set threshold.  
- 🌡️ **Environmental Monitoring**: Tracks real-time temperature, humidity, and soil moisture.  
- 📟 **OLED Display**: Shows live sensor data directly on the system.  
- 📲 **Blynk App Integration**: Remote monitoring and control via mobile app.  
- 🔔 **Custom Alerts**: Get notifications when soil moisture is low or the pump activates.  
- 🌐 **WiFi Connectivity**: Operates seamlessly in your home network.  

---

## 🛠️ **Installation Guide**  

### Step 1: Clone the Repository  
```bash  
git clone https://github.com/shanudhatirosh/Esp8266-progect-.git  
cd Esp8266-progect-
```  

### Step 2: Install Required Libraries  
Ensure the following libraries are installed in your Arduino IDE:  
- **Blynk** (for IoT app integration)  
- **Adafruit GFX** (graphics support for OLED)  
- **Adafruit SSD1306** (for OLED display communication)  
- **DHT Sensor Library** (for reading temperature and humidity)  

### Step 3: Upload the Code  
1. Open the project in **Arduino IDE**.  
2. Update these parameters in the code:  
   - **WiFi SSID and Password**  
   - **Blynk Auth Token**  
   - **Moisture Threshold**  
   - **Pump Run Time**  
3. Connect your ESP8266 NodeMCU to your computer and upload the code.  

---

## 📊 **Wiring Connections**  

### ESP8266 NodeMCU Pin Connections  
| **Component**       | **ESP8266 Pin** |  
|----------------------|-----------------|  
| OLED SDA            | D2 (GPIO 4)     |  
| OLED SCL            | D1 (GPIO 5)     |  
| DHT11 Data          | D4 (GPIO 2)     |  
| Soil Moisture Sensor| A0 (Analog)     |  
| Relay Signal        | D7 (GPIO 13)    |  
| Water Level Sensor (Optional) | D3 (GPIO 0) |  

### Circuit Diagram  
Create a neat and organized wiring setup. Consider using breadboards or soldering components onto a PCB for durability.  

---

## 📱 **Blynk App Setup**  

1. Download the **Blynk App** from the App Store or Google Play.  
2. Log in or create an account.  
3. Create a new project and select "ESP8266" as the device type.  
4. Add widgets:  
   - **Soil Moisture** (Virtual Pin: V1)  
   - **Temperature** (Virtual Pin: V2)  
   - **Humidity** (Virtual Pin: V3)  
5. Copy the **Auth Token** and update it in the Arduino code.  

---

## 🛠️ **Customization Options**  

- **Soil Moisture Threshold**: Adjust the threshold to suit your plant's watering needs.  
- **Notification Settings**: Configure the Blynk app to send alerts when moisture is low or the pump activates.  
- **Pump Duration**: Modify the duration for which the pump runs when triggered.  
- **Data Logging**: Add a microSD card module to log sensor data over time.  

---

## 💡 **Troubleshooting Tips**  

- **No Display Output?** Ensure correct OLED connections and library versions.  
- **WiFi Not Connecting?** Double-check WiFi credentials and signal strength.  
- **Pump Not Activating?** Verify relay and pump connections.  
- **Sensor Readings Incorrect?** Ensure sensors are correctly positioned and calibrated.  
- **No Blynk Data?** Recheck your Auth Token and Virtual Pin configurations.  

---

## 📜 **License**  

This project is licensed under the **MIT License**. Feel free to use, modify, and share it!  

---

## 🤝 **Contributing**  

We welcome contributions to enhance this project! To contribute:  
1. Fork the repository.  
2. Create a feature branch:  
   ```bash  
   git checkout -b feature-name  
   ```  
3. Commit your changes:  
   ```bash  
   git commit -m "Add feature"  
   ```  
4. Push to your branch:  
   ```bash  
   git push origin feature-name  
   ```  
5. Open a pull request for review.  

---

## 👤 **Author**  

**Shanudha Tirosh**  
- **GitHub**: [@Shanudhatirosh](https://github.com/Shanudhatirosh)  
- **Email**: [Tiroshbrot123@gmail.com](mailto:Tiroshbrot123@gmail.com)  

---

## 🌟 **Acknowledgments**  

Special thanks to:  
- **Blynk** for seamless IoT integration.  
- **Adafruit** for excellent sensor libraries.  
- **ESP8266 Community** for their support and resources.  

---

## 🏆 **Future Enhancements**  

- Add weather API integration for more intelligent watering based on forecast data.  
- Implement a web-based dashboard for enhanced control and monitoring.  
- Incorporate voice commands using Google Assistant or Alexa.  
- Extend compatibility to Raspberry Pi and other microcontrollers.  
