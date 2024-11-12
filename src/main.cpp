#include "Arduino.h"
#include "CurrentSensor.h"
#include "HardwareSerial.h"
#include <cstdint>

float mainVoltage = 12;

CurrentSensor RightSensor(36, 0.681 / 0.059, 0.15, mainVoltage);

void setup() {
  Serial.begin(115200);
  // Serial.begin(9600);
}

void loop() { RightSensor.monitor_current(); }
