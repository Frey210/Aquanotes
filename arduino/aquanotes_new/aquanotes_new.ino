#include <EEPROM.h>
#include "GravityTDS.h"
#include <OneWire.h>
#include <DallasTemperature.h>

// === Konstanta dan Pin Sensor ===
#define TDS_PIN A1
#define PH_PIN A2
#define DO_PIN A0
#define TEMP_PIN 2

// === Objek Sensor ===
GravityTDS gravityTds;
OneWire oneWire(TEMP_PIN);
DallasTemperature tempSensor(&oneWire);

// === Variabel Global ===
float tdsValue = 0;
float temperature = 25.0; // Default temperature
float pH = 0;
float voltage_pH4 = 4.6, voltage_pH7 = 4.18;
float pH4 = 4.0, pH7 = 7.0;
float slope, intercept;

// Variabel Dissolved Oxygen (DO)
#define VREF 5000    // VREF (mv)
#define ADC_RES 1024 // ADC Resolution
uint16_t ADC_Raw, ADC_Voltage, DO;
const uint16_t DO_Table[41] = {
    14460, 14220, 13820, 13440, 13090, 12740, 12420, 12110, 11810, 11530,
    11260, 11010, 10770, 10530, 10300, 10080, 9860, 9660, 9460, 9270,
    9080, 8900, 8730, 8570, 8410, 8250, 8110, 7960, 7820, 7690,
    7560, 7430, 7300, 7180, 7070, 6950, 6840, 6730, 6630, 6530, 6410};
#define CAL1_V 1600
#define CAL1_T 25

// === Fungsi Setup ===
void setup() {
  Serial.begin(115200);

  // Inisialisasi TDS
  gravityTds.setPin(TDS_PIN);
  gravityTds.setAref(5.0);  
  gravityTds.setAdcRange(1024);
  gravityTds.begin();

  // Inisialisasi pH
  slope = (pH7 - pH4) / (voltage_pH7 - voltage_pH4);
  intercept = pH4 - slope * voltage_pH4;

  // Inisialisasi Sensor Suhu
  tempSensor.begin();
}

// === Fungsi Loop ===
void loop() {
  // Baca suhu
  temperature = readTemperature();

  // TDS Sensor
  readTDS();

  // pH Sensor
  readPH();

  // DO Sensor
  readDO();

  // Tampilkan data ke serial monitor
  displayReadings();

  delay(1000);
}

// === Fungsi Membaca Suhu ===
float readTemperature() {
  tempSensor.requestTemperatures();
  return tempSensor.getTempCByIndex(0);
}

// === Fungsi Membaca TDS ===
void readTDS() {
  gravityTds.setTemperature(temperature);
  gravityTds.update();
  tdsValue = gravityTds.getTdsValue();
}

// === Fungsi Membaca pH ===
void readPH() {
  int pH_Value = analogRead(PH_PIN);
  float Voltage = pH_Value * (5.0 / 1023.0);
  pH = slope * Voltage + intercept;
}

// === Fungsi Membaca Dissolved Oxygen (DO) ===
void readDO() {
  ADC_Raw = analogRead(DO_PIN);
  ADC_Voltage = uint32_t(VREF) * ADC_Raw / ADC_RES;
  DO = calculateDO(ADC_Voltage, temperature);
}

uint16_t calculateDO(uint32_t voltage_mv, uint8_t temperature_c) {
  uint16_t V_saturation = (uint32_t)CAL1_V + (uint32_t)35 * temperature_c - (uint32_t)CAL1_T * 35;
  return (voltage_mv * DO_Table[temperature_c] / V_saturation);
}

// === Fungsi Menampilkan Data ===
void displayReadings() {
  Serial.println("=====================");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("TDS: ");
  Serial.print(tdsValue);
  Serial.println(" ppm");

  Serial.print("pH: ");
  Serial.println(pH);

  Serial.print("DO: ");
  Serial.println(DO);
  Serial.println("=====================");
}
