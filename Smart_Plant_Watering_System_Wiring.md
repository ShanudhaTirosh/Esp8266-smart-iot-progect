
# Smart Plant Watering System - Wiring Details

This document describes the wiring for the Smart Plant Watering System using an ESP8266 NodeMCU, DHT11, Soil Moisture Sensor, Relay Module, OLED Display, and a Water Pump.

## Components Required
- **NodeMCU ESP8266**: Microcontroller board.
- **DHT11**: Temperature and humidity sensor.
- **Soil Moisture Sensor**: Analog sensor to measure soil moisture.
- **Relay Module**: To control the water pump.
- **OLED Display (SSD1306, I2C)**: For data visualization.
- **Water Pump**: For irrigation.
- **Resistors**: 10kΩ pull-up resistor for DHT11.
- **Connecting Wires**: Male-to-Male and Male-to-Female jumper wires.
- **Power Source**: 3.3V/5V from NodeMCU or external power supply for the pump.

---

## Wiring Diagram
Below are the detailed wiring connections for each component.

### **1. ESP8266 NodeMCU**
| **NodeMCU Pin** | **Connection**          |
|------------------|-------------------------|
| `Vin`            | External 5V power source (optional for higher loads) |
| `3.3V`           | Power for DHT11, OLED, and Soil Moisture Sensor       |
| `GND`            | Ground for all components                             |
| `A0`             | Soil Moisture Sensor Signal Pin                      |
| `D4 (GPIO2)`     | DHT11 Data Pin                                       |
| `D7 (GPIO13)`    | Relay IN Pin                                         |
| `D1 (GPIO5)`     | OLED SCL (Clock)                                     |
| `D2 (GPIO4)`     | OLED SDA (Data)                                      |

---

### **2. Soil Moisture Sensor**
| **Sensor Pin** | **Connection**    |
|----------------|-------------------|
| `VCC`          | `3.3V` NodeMCU    |
| `GND`          | `GND` NodeMCU     |
| `Signal`       | `A0` NodeMCU      |

---

### **3. DHT11 Temperature & Humidity Sensor**
| **DHT11 Pin** | **Connection**    |
|---------------|-------------------|
| `VCC`         | `3.3V` NodeMCU    |
| `GND`         | `GND` NodeMCU     |
| `DATA`        | `D4 (GPIO2)`      |

**Note:** Use a **10kΩ pull-up resistor** between the `DATA` pin and `VCC` for stable operation.

---

### **4. Relay Module**
| **Relay Pin** | **Connection**    |
|---------------|-------------------|
| `VCC`         | `3.3V` NodeMCU    |
| `GND`         | `GND` NodeMCU     |
| `IN`          | `D7 (GPIO13)`     |
| `COM`         | Pump Positive Terminal (from external power source) |
| `NO`          | Pump Positive Wire                                  |

---

### **5. OLED Display (SSD1306, I2C)**
| **OLED Pin** | **Connection**    |
|--------------|-------------------|
| `VCC`        | `3.3V` NodeMCU    |
| `GND`        | `GND` NodeMCU     |
| `SCL`        | `D1 (GPIO5)`      |
| `SDA`        | `D2 (GPIO4)`      |

---

### **6. Water Pump**
| **Pump Wire** | **Connection**    |
|---------------|-------------------|
| `+` (Positive)| Relay `NO` terminal |
| `-` (Negative)| External Power Ground |

---

### **7. External Power Supply (For Water Pump)**
| **Power Supply Pin** | **Connection**       |
|-----------------------|----------------------|
| `+`                  | Relay `COM` terminal |
| `-`                  | Common GND with NodeMCU |

---

## Additional Notes
1. Ensure all **grounds are connected together** for proper operation.
2. Use a **1N4007 diode** across the water pump terminals to protect the circuit from back EMF when the relay switches off.
3. Double-check your relay module's voltage rating. If it requires 5V but you're using a NodeMCU (3.3V), consider using a transistor to drive the relay or a 5V relay module with an onboard transistor.

---

## Powering the System
- Power the NodeMCU using a USB cable (5V via Vin) or an external 5V power supply.
- For the water pump, use an external power source with a voltage rating matching your pump's requirements (e.g., 5V, 12V).

---

## Wiring Diagram (Text)
```
NodeMCU:
  - 3.3V --> DHT11 VCC, OLED VCC, Soil Sensor VCC
  - GND  --> DHT11 GND, OLED GND, Soil Sensor GND, Relay GND
  - A0   --> Soil Sensor Signal
  - D4   --> DHT11 DATA (with 10k pull-up to 3.3V)
  - D7   --> Relay IN
  - D1   --> OLED SCL
  - D2   --> OLED SDA

Relay:
  - COM  --> Pump Positive Wire
  - NO   --> Pump Positive Terminal (from external power)
  - External GND --> Pump Negative Wire
```

---

## Troubleshooting
1. If the OLED display does not work:
   - Check I2C connections (SCL and SDA).
   - Verify the I2C address (default: `0x3C`).
2. If the relay doesn’t activate:
   - Confirm the `IN` pin voltage matches the relay requirements (3.3V or 5V).
3. If the DHT11 fails:
   - Verify the 10k pull-up resistor is installed on the `DATA` pin.
   - Check the wiring for loose connections.

---

Happy Building!
