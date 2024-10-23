#include "Arduino.h"
#include "HardwareSerial.h"
#include "stdint.h"

const int currentPin = 36;
uint32_t currentValue;

void setup() {
  Serial.begin(115200);
  // Serial.begin(9600);
}

void loop() {
  currentValue = analogRead(currentPin);
  Serial.println(currentValue, DEC); // print as an ASCII-encoded decimal
  delay(10);
}
