#include "Arduino.h"
#include "HardwareSerial.h"
#include "stdint.h"

const int currentSensingPin = 36;
const int mainVoltage = 12;
float amplification = 0.681/0.059;
float shuntResistance = 0.15;

uint32_t adcShunt;
float voltageSensor;
float resistensValue;
float voltageValue;
float currentValue;



void setup() {
  Serial.begin(115200);
  // Serial.begin(9600);
  
  // clear screen
    Serial.write(27);
  Serial.print("[2J");

  // Hide curser
    Serial.write(27);
  Serial.print("[?25I");


}

void loop() {

  Serial.write(27);
  Serial.print("[0;0H");


  //analog read resultat print
  adcShunt = analogRead(currentSensingPin);
  Serial.print("Adc value: ");
    Serial.write(27);
  Serial.print("[K");
  Serial.println(adcShunt, DEC); // print as an ASCII-encoded decimal

  //voltage in hall effekt pin
  voltageValue = adcShunt*3.3/4095;
  Serial.print("Amplified shunt voltage: ");
      Serial.write(27);
  Serial.print("[K");
  Serial.println(voltageValue, DEC);


  //calculating voltage over shunt and printing
  voltageSensor = (voltageValue/amplification);
  //voltageSensor = map(hallEffektValue, 1.5 , 3.5 , -5 , 5); // Mapper værdien til bage til ampere
  Serial.print("Voltage over shunt: ");
      Serial.write(27);
  Serial.print("[K");
  Serial.println(voltageSensor, DEC); 


  //calculating current value and printing
  currentValue = (voltageSensor/shuntResistance);
  Serial.print("Total current: "); 
      Serial.write(27);
  Serial.print("[K");
  Serial.println(currentValue, DEC);
  
  //calculating ressistence value
  resistensValue = mainVoltage/currentValue; // beregner resistencen
  Serial.print("Total resistance: ");
      Serial.write(27);
  Serial.print("[K");
  Serial.println(resistensValue, DEC); 
 
}
