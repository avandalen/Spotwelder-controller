/********************************************************************/
// Thermocouple
/********************************************************************/

// Deze lib gebruiken:
// https://github.com/JChristensen/Thermocouple

// this example is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple

/*#include "max6675.h"

int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
int vccPin = 3;
int gndPin = 2;*/
  
void testMAX6675() {
  int MAX6675_MISO = 12;
  int MAX6675_CS = 6;
  int MAX6675_SCLK = 13;

  MAX6675 thermocouple(MAX6675_SCLK, MAX6675_CS, MAX6675_MISO);
  //int vccPin = 3;
  //int gndPin = 2;

  Serial.begin(9600);
  // use Arduino pins 
  //pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH);
  //pinMode(gndPin, OUTPUT); digitalWrite(gndPin, LOW);
  
  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  delay(500);

while(1) {
  // basic readout test, just print the current temp
  
   Serial.print("C = "); 
   Serial.println(thermocouple.readCelsius());
   Serial.print("F = ");
   Serial.println(thermocouple.readFahrenheit());
 
   delay(1000);
}
}
