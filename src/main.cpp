#include "Arduino.h"
#include "HardwareSerial.h"
#include "stdint.h"

const int hallEffektPin = 36;
const int voltageValueWire = 12;
uint32_t hallEffektValue;
float currentValue;
float resistensValue;
float voltageValue;

void setup() {
  Serial.begin(115200);
  // Serial.begin(9600);
}

void loop() {
  hallEffektValue = analogRead(hallEffektPin);
  Serial.println(hallEffektValue, DEC); // print as an ASCII-encoded decimal
  delay(10);
  voltageValue = hallEffektValue*5/1023;
  currentValue = (voltageValue-2.5)/0.185;
  //currentValue = map(hallEffektValue, 1.5 , 3.5 , -5 , 5); // Mapper værdien til bage til ampere
  Serial.println(currentValue, DEC); // print as an ASCII-encoded decimal
  delay(10);
  resistensValue = voltageValueWire/currentValue; // beregner resistencen
  Serial.println(resistensValue, DEC); // print as an ASCII-encoded decimal
  delay(10);
}
