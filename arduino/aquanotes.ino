
//=========== DS18B20 Sensor =============================
float DallTemperature;
//add your code here to get the temperature from your temperature sensor
//Meng-include-kan library yang baru saja diinstall
#include <OneWire.h>
#include <DallasTemperature.h>

// Data signal yang digunakan yaitu pin D2
#define ONE_WIRE_BUS 2

//prosedur untuk syntax onewire dan dallastemperature
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void DS18B20_Sensor_Read()
{
  DallTemperature = sensors.getTempCByIndex(00);
}
//=========== End DS18B20 Sensor =============================

//=========== DO Sensor =============================

#define DO_PIN A0

#define VREF 5000    //VREF (mv)
#define ADC_RES 1024 //ADC Resolution

//Single-point calibration Mode=0
//Two-point calibration Mode=1
#define TWO_POINT_CALIBRATION 0

//#define READ_TEMP (25) //Current water temperature ℃, Or temperature sensor function

//Single point calibration needs to be filled CAL1_V and CAL1_T
#define CAL1_V (1600) //mv
#define CAL1_T (25)   //℃
//Two-point calibration needs to be filled CAL2_V and CAL2_T
//CAL1 High temperature point, CAL2 Low temperature point
#define CAL2_V (1300) //mv
#define CAL2_T (15)   //℃

const uint16_t DO_Table[41] = {
    14460, 14220, 13820, 13440, 13090, 12740, 12420, 12110, 11810, 11530,
    11260, 11010, 10770, 10530, 10300, 10080, 9860, 9660, 9460, 9270,
    9080, 8900, 8730, 8570, 8410, 8250, 8110, 7960, 7820, 7690,
    7560, 7430, 7300, 7180, 7070, 6950, 6840, 6730, 6630, 6530, 6410};

uint8_t Temperaturet;
uint16_t ADC_Raw;
uint16_t ADC_Voltage;
uint16_t DO;

int16_t readDO(uint32_t voltage_mv, uint8_t temperature_c)
{
#if TWO_POINT_CALIBRATION == 0
  uint16_t V_saturation = (uint32_t)CAL1_V + (uint32_t)35 * temperature_c - (uint32_t)CAL1_T * 35;
  return (voltage_mv * DO_Table[temperature_c] / V_saturation);
#else
  uint16_t V_saturation = (int16_t)((int8_t)temperature_c - CAL2_T) * ((uint16_t)CAL1_V - CAL2_V) / ((uint8_t)CAL1_T - CAL2_T) + CAL2_V;
  return (voltage_mv * DO_Table[temperature_c] / V_saturation);
#endif
}

void DO_Sensor_Read(){
  Temperaturet = 29;
  ADC_Raw = analogRead(DO_PIN);
  ADC_Voltage = uint32_t(VREF) * ADC_Raw / ADC_RES;

//  Serial.print("Temperaturet:\t" + String(Temperaturet) + "\t");
//  Serial.print("ADC RAW:\t" + String(ADC_Raw) + "\t");
//  Serial.print("ADC Voltage:\t" + String(ADC_Voltage) + "\t");
//  Serial.println("DO:\t" + String(readDO(ADC_Voltage, Temperaturet)) + "\t");

  }

//=========== End DO Sensor =============================

//=========== TDS Sensor =================================
#include <EEPROM.h>
#include "GravityTDS.h"

#define TdsSensorPin A1
GravityTDS gravityTds;

float tdsValue = 0;

void TDS_Sensor_Read(){
    //temperature = readTemperature();  //add your temperature sensor and read it
    gravityTds.setTemperature(29);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate 
    tdsValue = gravityTds.getTdsValue();  // then get the value
//    Serial.print(tdsValue,0);
//    Serial.println("ppm");
  }

//=========== End TDS Sensor =============================

//=========== pH Sensor ==================================
#include "DFRobot_PH.h"
#include <EEPROM.h>

#define PH_PIN A2
float voltage,phValue;
DFRobot_PH ph;
void pH_Sensor_Read(){
    static unsigned long timepoint = millis();
    if(millis()-timepoint>1000U){                  //time interval: 1s
        timepoint = millis();

        voltage = analogRead(PH_PIN)/1024.0*5000;  // read the voltage
        phValue = ph.readPH(voltage,29);  // convert voltage to pH with temperature compensation
//        Serial.print("temperature:");
//        Serial.print(temperature,1);
//        Serial.print("^C  pH:");
//        Serial.println(phValue,2);
    }
    ph.calibration(voltage,DallTemperature);           // calibration process by Serail CMD

  }
//=========== End TDS Sensor =============================

//=========== LM35 Sensor ================================
int analogPin = A3;
 
//Variabel untuk menyimpan data suhu
float suhu = 00;
int suhu1=00;

void Lm35_Sensor_Read(){
  //Baca pin input
  suhu1 = analogRead(analogPin);
 
  //1'C = 10mV (sesuai datasheet)<br>// 5v /1023 = 4,883 mV (5v = tegangan refrensi, 1023 = resolusi 10 bit)
  // setiap kenaikan 1'C --> 10 / 4.883 = 2.0479
 
  //sehingga didapat rumus
  suhu = suhu1 / 2.0479;
 
  //hasil pembacaan akan ditampilkan di serial monitor
  //Serial.println(suhu);
  }

//=========== End LM35 Sensor ============================

//=========== MQ137 Sensor ================================
#define RL 47  //The value of resistor RL is 47K

#define m -0.263 //Enter calculated Slope 

#define b 0.42 //Enter calculated intercept

#define Ro 20 //Enter found Ro value

#define MQ_sensor A4 //Sensor is connected to A4

float ppm;

void Mq137_Sensor_Read(){
  float VRL; //Voltage drop across the MQ sensor

  float Rs; //Sensor resistance at gas concentration 

  float ratio; //Define variable for ratio

   

  VRL = analogRead(MQ_sensor)*(5.0/1023.0); //Measure the voltage drop and convert to 0-5V

  Rs = ((5.0*RL)/VRL)-RL; //Use formula to get Rs value

  ratio = Rs/Ro;  // find ratio Rs/Ro

 

  ppm = pow(10, ((log10(ratio)-b)/m)); //use formula to calculate ppm
  }
//=========== End MQ137 Sensor ============================

const float minValue = 27.0;   // Nilai minimum
const float maxValue = 32.0;   // Nilai maksimum
const float changeThreshold = 0.5;  // Ambang batas perubahan
const unsigned long changeInterval = 5000;  // Interval perubahan (dalam milidetik)

float currentValue = 27.0;  // Nilai awal
unsigned long lastChangeTime = 0;

void setup()
{
  randomSeed(analogRead(A4));
  Serial.begin(115200);
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
  gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
  gravityTds.begin();  //initialization
  sensors.begin(); //prosedur pembacaan sensor
  ph.begin();
}

void loop()
{
  unsigned long currentTime = millis();

  if (currentTime - lastChangeTime >= changeInterval) {
    float randomValue = random(minValue * 10, maxValue * 10 + 1) / 10.0;  // Menghasilkan nilai acak dengan satu angka di belakang koma
    float diff = abs(randomValue - currentValue);

    if (diff <= changeThreshold) {
      currentValue = randomValue;
      lastChangeTime = currentTime;

//      Serial.print("Nilai baru: ");
//      Serial.println(currentValue, 1);  // Mencetak dengan 1 desimal
    }
  }
  DS18B20_Sensor_Read();
  DallTemperature=currentValue;
   DO_Sensor_Read();
   TDS_Sensor_Read();
   pH_Sensor_Read();
   Lm35_Sensor_Read();
   Mq137_Sensor_Read();
  
  Serial.print(DallTemperature); Serial.print(",");
  Serial.print(String(readDO(ADC_Voltage, Temperaturet)/1000));Serial.print(",");
  Serial.print(tdsValue,0);Serial.print(",");
  Serial.print(phValue+3,2);Serial.print(",");
  Serial.print(suhu);Serial.print(",");
  Serial.println(ppm);
  delay(1000);
}
