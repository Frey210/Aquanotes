#include <DallasTemperature.h>
#include <OneWire.h>
#include "GravityTDS.h"

// === Konstanta dan Pin Sensor ===
#define TDS_PIN A1
#define PH_PIN A2
#define DO_PIN A0
#define TEMP_PIN 2

// Library and Object Initialization
OneWire oneWire(TEMP_PIN);
DallasTemperature temperatureSensor(&oneWire);
GravityTDS gravityTDS;

float waterTemperature = 0.0, tdsValue = 0.0, pHValue = 0.0, doValue = 0.0;

// DO Table and Configuration
#define VREF 5000    // Voltage reference (in millivolts)
#define ADC_RES 1024 // ADC resolution
#define CAL1_V 1600  // Calibration voltage for DO
#define CAL1_T 25    // Calibration temperature for DO
const uint16_t DO_Table[41] = {14460, 14220, 13820, /*...*/ 6530, 6410};

int16_t readDO(uint32_t voltage_mv, uint8_t temperature_c) {
  uint16_t V_saturation = (uint32_t)CAL1_V + (uint32_t)35 * temperature_c - (uint32_t)CAL1_T * 35;
  return (voltage_mv * DO_Table[temperature_c] / V_saturation);
}

void setup() {
  Serial.begin(9600);
  temperatureSensor.begin();
  gravityTDS.setPin(TDS_PIN);
  gravityTDS.setAref(5.0);
  gravityTDS.setAdcRange(1024);
  gravityTDS.begin();
}

void loop() {
  // Temperature
  temperatureSensor.requestTemperatures();
  waterTemperature = temperatureSensor.getTempCByIndex(0);

  // TDS
  gravityTDS.setTemperature(waterTemperature);
  gravityTDS.update();
  tdsValue = gravityTDS.getTdsValue();

  // pH
  float pHVoltage = analogRead(PH_PIN) * (5.0 / 1023.0);
  pHValue = (7.0 - (pHVoltage - 4.18) * (3.0 / 0.42)); // Example calibration formula

  // DO
  uint16_t rawADC = analogRead(DO_PIN);
  uint16_t voltage = (uint32_t)VREF * rawADC / ADC_RES;
  doValue = readDO(voltage, (uint8_t)waterTemperature);

  // Kirim data dalam format CSV
  Serial.print(waterTemperature);
  Serial.print(",");
  Serial.print(doValue);
  Serial.print(",");
  Serial.print(tdsValue);
  Serial.print(",");
  Serial.println(pHValue);

  delay(1000);
}
