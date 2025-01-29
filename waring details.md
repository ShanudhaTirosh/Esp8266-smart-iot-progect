I'll provide detailed pin connections and create a visual diagram for your smart plant watering system.



Detailed Pin Connections:

1. Power Supply to NodeMCU:
```
5V Power Supply → NodeMCU
+ (5V)  → Vin
- (GND) → GND
```

2. OLED Display:
```
OLED    → NodeMCU
VCC     → 3.3V
GND     → GND
SCL     → D1 (GPIO5)
SDA     → D2 (GPIO4)
```

3. DHT11 Temperature/Humidity Sensor:
```
DHT11   → NodeMCU
VCC     → 3.3V
GND     → GND
DATA    → D4
```

4. Capacitive Soil Moisture Sensor:
```
Sensor  → NodeMCU
VCC     → 3.3V
GND     → GND
AOUT    → A0
```

5. Relay Module:
```
Relay   → NodeMCU
VCC     → 3.3V
GND     → GND
IN      → D13 (GPIO13)
```

Important Notes:
1. All GND connections should be common
2. Use 3.3V for all sensors
3. Ensure secure connections
4. Keep water away from electronics
5. Double-check all connections before powering on

The diagram above shows:
- Red lines: Power connections (5V/3.3V)
- Black lines: Ground connections
- Blue lines: Data/signal connections
- Component layout and pin mappings

Would you like me to explain any specific connection in more detail?