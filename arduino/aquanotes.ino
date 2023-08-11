
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
