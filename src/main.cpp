#include "Arduino.h"
#include "CurrentSensor.h"
#include "HardwareSerial.h"
#include "esp32-hal.h"
#include <cstdint>

float mainVoltage = 12;

enum Wire : unsigned char {
  RightBlink = 0b1,
  LeftBlink = 0b10,
  RightLight = 0b100,
  LeftLight = 0b1000,
  Brake = 0b10000,
  Fog = 0b100000,
};

CurrentSensor RightSensor(RightBlink, 39, 36, 23, 0.681 / 0.059, 0.15,
                          mainVoltage);

void setup() {
  Serial.begin(115200);
  // Serial.begin(9600);
}

void loop() {
  unsigned char errorBite;

  errorBite = errorBite | RightSensor.monitor_current();

  Serial.print("Error code: ");
  Serial.println(errorBite, BIN);
  delay(100);
}
