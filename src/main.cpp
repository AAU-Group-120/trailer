#include "Arduino.h"
#include "BluetoothSerial.h"
#include "CurrentSensor.h"
#include "HardwareSerial.h"
#include "esp32-hal.h"
#include "stdint.h"
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

unsigned char fejl = 0b0000001;
int tidligerFejl = 0;
uint32_t i = 0;

BluetoothSerial SerialBT; // Create a Bluetooth Serial object
void setup() {
  Serial.begin(115200); // Initialize serial monitor
  SerialBT.begin(
      "ESP32_Transmitter"); // Set Bluetooth name to "ESP32_Transmitter"
  Serial.println("Bluetooth Device is ready to pair");
}

void loop() {
  // message(fejl);
  // delay(1000); // Wait 30 seconds before sending again
  if (fejl != tidligerFejl) {
    tidligerFejl = fejl;
    SerialBT.print(fejl);
    Serial.println(fejl);
  }

  i++;
  if (i > 1800000) {
    fejl = (fejl + 1) % 64;
    i = 0;
  }

  unsigned char errorBite;

  errorBite = errorBite | RightSensor.monitor_current();

  Serial.print("Error code: ");
  Serial.println(errorBite, BIN);
  delay(500);
}
