# 🌱 Smart Plant Watering System 🌱

A smart plant watering system that automatically monitors soil moisture, temperature, and humidity using ESP8266 NodeMCU.

## 📦 Components Required

- ESP8266 NodeMCU
- DHT11 Temperature & Humidity Sensor
- Soil Moisture Sensor
- OLED Display (SSD1306)
- Relay Module
- Water Pump
- Jumper Wires

## ⚙️ Features

- Automatic plant watering
- Real-time temperature and humidity monitoring
- OLED display for sensor readings
- Blynk app integration for remote monitoring

## 🛠️ Installation

1. Clone the repository
   ```bash
   git clone https://github.com/shanudhatirosh/Esp8266-progect-.git
   ```

2. Install Required Libraries:
   - Blynk
   - Adafruit GFX
   - Adafruit SSD1306
   - DHT sensor library

3. Upload Code:
   - Open in Arduino IDE
   - Update WiFi credentials
   - Upload to ESP8266 NodeMCU

## 📊 Wiring Connections

| Component | ESP8266 Pin |
|-----------|-------------|
| OLED SDA | D2 (GPIO 4) |
| OLED SCL | D1 (GPIO 5) |
| DHT11 Data | D4 (GPIO 2) |
| Soil Moisture | A0 (Analog) |
| Relay Signal | D7 (GPIO 13) |

## 📱 Blynk Setup

1. Download Blynk app
2. Create new project
3. Add widgets for:
   - Soil Moisture (V1)
   - Temperature (V2)
   - Humidity (V3)

## 🔧 Configuration

Modify these parameters in the code:
- WiFi SSID
- WiFi Password
- Blynk Auth Token
- Moisture Threshold
- Pump Run Time

## 💡 Troubleshooting

- Check all connections
- Verify library installations
- Ensure proper power supply
- Monitor serial output for debugging

## 📜 License

MIT License

## 🤝 Contributing

1. Fork the repository
2. Create your feature branch
3. Commit changes
4. Push to the branch
5. Create pull request

## 👤 Author

[SHANUDHA TIROSH]
- GitHub: [@Shanudhatirosh]
- Email: Tiroshbrot123@gmail.com

## 🌟 Acknowledgments

- Blynk
- Adafruit
- ESP8266 Community
