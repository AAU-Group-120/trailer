#include "Arduino.h"
#include "BluetoothSerial.h"
#include "CurrentSensor.h"
#include "HardwareSerial.h"
#include "WString.h"
#include "esp32-hal.h"
#include "stdint.h"
#include <cstdint>

#define ACK 0b110
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

unsigned char lastErrorByte = 0b0;

uint32_t delayTime = 1000; // in miliseconds
uint32_t lastDelayTime = millis();

uint32_t ackTime = 1000; // in miliseconds
uint32_t lastAckTime = millis();

BluetoothSerial SerialBT; // Create a Bluetooth Serial object
void setup() {
  Serial.begin(115200); // Initialize serial monitor
  SerialBT.begin(
      "ESP32_Transmitter"); // Set Bluetooth name to "ESP32_Transmitter"
  Serial.println("Bluetooth Device is ready to pair");
}

void loop() {

  if ((lastDelayTime + delayTime) < millis()) {
    lastDelayTime = millis();

    unsigned char errorBite = 0b0;

    errorBite = errorBite | RightSensor.monitor_current();

    // errorBite = errorBite | LeftBlink | LeftLight;

    unsigned char data = 0b0;

    if (errorBite != lastErrorByte) {
      lastErrorByte = errorBite;
      SerialBT.print(errorBite);
    }

    while (!(data == ACK)) {

      if (SerialBT.available()) {
        String recivedData = SerialBT.readString();
        data = recivedData[recivedData.length() - 1];
        Serial.println(data, BIN);
      }

      if ((lastAckTime + ackTime) < millis()) {
        lastAckTime = millis();

        SerialBT.write(errorBite);
        SerialBT.write(0b10000000);
        // SerialBT.print("\0");

        Serial.print("Error code: ");
        Serial.println(errorBite, BIN);
      }
    }
  }
}
