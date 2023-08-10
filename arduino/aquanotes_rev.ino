#include <OneWire.h>
#include <DallasTemperature.h>
#include "DFRobot_PH.h"
#include <EEPROM.h>
#include "GravityTDS.h"

// DS18B20 Sensor
float DallTemperature;
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// DO Sensor
#define DO_PIN A0
#define VREF 5000
#define ADC_RES 1024
#define TWO_POINT_CALIBRATION 0
#define CAL1_V (1600)
#define CAL1_T (25)
#define CAL2_V (1300)
#define CAL2_T (15)
const uint16_t DO_Table[41] = { /* ... */ };
uint8_t Temperaturet;
uint16_t ADC_Raw;
uint16_t ADC_Voltage;
uint16_t DO;

// TDS Sensor
#define TdsSensorPin A1
GravityTDS gravityTds;
float tdsValue = 0;

// pH Sensor
#define PH_PIN A2
float voltage, phValue;
DFRobot_PH ph;

// LM35 Sensor
int analogPin = A3;
float suhu = 0;
int suhu1 = 0;

// MQ137 Sensor
#define RL 47
#define m -0.263
#define b 0.42
#define Ro 20
#define MQ_sensor A4
float ppm;

void setup() {
  Serial.begin(115200);
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);
  gravityTds.setAdcRange(1024);
  gravityTds.begin();
  sensors.begin();
  ph.begin();
}

void loop() {
  DS18B20_Sensor_Read();
  DO_Sensor_Read();
  TDS_Sensor_Read();
  pH_Sensor_Read();
  Lm35_Sensor_Read();
  Mq137_Sensor_Read();
  
  Serial.print(DallTemperature); Serial.print(",");
  Serial.print(String(readDO(ADC_Voltage, Temperaturet))); Serial.print(",");
  Serial.print(tdsValue, 0); Serial.print(",");
  Serial.print(phValue, 2); Serial.print(",");
  Serial.print(suhu); Serial.print(",");
  Serial.println(ppm);
  delay(1000);
}

void DS18B20_Sensor_Read() {
  sensors.requestTemperatures();
  DallTemperature = sensors.getTempCByIndex(0);
}

void DO_Sensor_Read() {
  Temperaturet = DallTemperature;
  ADC_Raw = analogRead(DO_PIN);
  ADC_Voltage = uint32_t(VREF) * ADC_Raw / ADC_RES;
}

void TDS_Sensor_Read() {
  gravityTds.setTemperature(DallTemperature);
  gravityTds.update();
  tdsValue = gravityTds.getTdsValue();
}

void pH_Sensor_Read() {
  static unsigned long timepoint = millis();
  if (millis() - timepoint > 1000U) {
    timepoint = millis();
    voltage = analogRead(PH_PIN) / 1024.0 * 5000;
    phValue = ph.readPH(voltage, DallTemperature);
  }
  ph.calibration(voltage, DallTemperature);
}

void Lm35_Sensor_Read() {
  suhu1 = analogRead(analogPin);
  suhu = suhu1 / 2.0479;
}

void Mq137_Sensor_Read() {
  float VRL;
  float Rs;
  float ratio;
  VRL = analogRead(MQ_sensor) * (5.0 / 1023.0);
  Rs = ((5.0 * RL) / VRL) - RL;
  ratio = Rs / Ro;
  ppm = pow(10, ((log10(ratio) - b) / m));
}
