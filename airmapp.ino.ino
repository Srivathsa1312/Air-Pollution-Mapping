#include "DHTesp.h"
#include <TinyGPS++.h>

// ---------------- PINS ----------------
#define DUST_PIN 34
#define LED_PIN 25
#define MQ135_PIN 35
#define DHT_PIN 15

#define RXD2 16
#define TXD2 17

DHTesp dht;
TinyGPSPlus gps;
HardwareSerial gpsSerial(2);

// ---------------- MQ135 ----------------
int getMQ135() {
  long sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(MQ135_PIN);
    delay(20);
  }
  return sum / 10;
}

// ---------------- AQI ----------------
int calculateAQI(float pm25) {
  if (pm25 <= 12) return map(pm25, 0, 12, 0, 50);
  else if (pm25 <= 35) return map(pm25, 12, 35, 51, 100);
  else if (pm25 <= 55) return map(pm25, 35, 55, 101, 150);
  else if (pm25 <= 150) return map(pm25, 55, 150, 151, 200);
  else return 300;
}

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  dht.setup(DHT_PIN, DHTesp::DHT11);
  gpsSerial.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

// ---------------- LOOP ----------------
void loop() {

  // ===== DUST SENSOR (UPDATED FORMULA) =====
  int sum = 0;

  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_PIN, LOW);
    delayMicroseconds(280);

    int raw = analogRead(DUST_PIN);

    delayMicroseconds(40);
    digitalWrite(LED_PIN, HIGH);
    delayMicroseconds(9680);

    sum += raw;
  }

  int avgRaw = sum / 5;

  // Step 1: ADC → Voltage
  float voltage = avgRaw * (3.3 / 4095.0);

  // Step 2: Voltage → Dust (mg/m³)
  float dust_mg = (voltage - 0.1) / 0.5;

  if (dust_mg < 0) dust_mg = 0;

  // Step 3: Convert to µg/m³
  float pm25 = dust_mg * 0.0;

  // ===== AQI =====
  int AQI = calculateAQI(pm25);

  // ===== MQ135 =====
  int mq = getMQ135();

  // ===== DHT =====
  float temp = dht.getTemperature();
  float hum = dht.getHumidity();

  // ===== GPS =====
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  // ===== OUTPUT =====
  Serial.println("\n====== AIR QUALITY REPORT ======");

  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  Serial.print("PM2.5: ");
  Serial.print(pm25);
  Serial.println(" ug/m3");

  Serial.print("AQI: ");
  Serial.println(AQI);

  if (AQI <= 50) Serial.println("Status: GOOD 🟢");
  else if (AQI <= 100) Serial.println("Status: MODERATE 🟡");
  else Serial.println("Status: UNHEALTHY 🔴");

  Serial.print("MQ135: ");
  Serial.println(mq);

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" C  Humidity: ");
  Serial.println(hum);

  if (gps.location.isValid()) {
    Serial.print("Lat: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Lng: ");
    Serial.println(gps.location.lng(), 6);
  } else {
    Serial.println("GPS: No Fix");
  }

  Serial.println("================================");

  delay(2000);
}
