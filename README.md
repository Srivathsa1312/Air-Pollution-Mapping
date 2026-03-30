**Low-Cost Air Quality Monitoring Device (ESP32)**

  This project is a low-cost air quality monitoring system built using an ESP32 microcontroller. It measures environmental parameters like air pollution, dust particles, temperature, humidity, and location.

**Features**
--> Air quality detection using MQ135 gas sensor
--> Dust particle measurement
--> Temperature & humidity monitoring
--> GPS-based location tracking
--> Battery-powered with voltage regulation
--> Active airflow system using a fan
--> Real-time data processing with ESP32

----------------------------------------------------------------
| Component        | Description                                |
| ---------------- | ------------------------------------------ |
| ESP32            | Main microcontroller with WiFi & Bluetooth |
| MQ135 Gas Sensor | Detects air pollutants (CO₂, NH₃, etc.)    |
| Dust Sensor      | Measures particulate matter (PM)           |
| DHT11            | Temperature and humidity sensor            |
| GPS Module       | Provides location data                     |
| Li-ion Battery   | Power source                               |
| Buck Converter   | Voltage regulation                         |
| Fan              | Improves airflow for accurate sensing      |

----------------------------------------------------------------
**General Connection Summary**
-MQ135 → Analog pin of ESP32
-Dust Sensor → Digital/Analog input
-DHT11 → Digital GPIO pin
-GPS Module → UART (TX/RX)
-Fan → Powered via buck converter
-Battery → Buck Converter → ESP32 VIN

**Working Principle**
-Sensors collect environmental data:
-Gas concentration (MQ135)
-Dust particles
-Temperature & humidity (DHT11)
-GPS coordinates
-ESP32 processes the data.
-Data can be:
  Displayed on Serial Monitor
  Sent to cloud (if WiFi is enabled)
  Fan ensures proper airflow for accurate readings.

**Software Setup**
1. Install Arduino IDE
Download from: https://www.arduino.cc/en/software

2. Install ESP32 Board
Go to File → Preferences
Add this URL:
https://dl.espressif.com/dl/package_esp32_index.json
Install ESP32 from Board Manager

3. Install Required Libraries
DHT sensor library
TinyGPS++ (for GPS)

Upload Code
Open the .ino file
Select board: ESP32 Dev Module
Choose correct COM port
Click Upload
