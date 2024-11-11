#include "Arduino.h"
#include "HardwareSerial.h"
#include "stdint.h"
#include "BluetoothSerial.h"


char chartosend = '1';

BluetoothSerial SerialBT;     // Create a Bluetooth Serial object

void setup() {
  Serial.begin(115200);        // Initialize serial monitor
  SerialBT.begin("ESP32_Transmitter"); // Set Bluetooth name to "ESP32_Transmitter"
  Serial.println("Bluetooth Device is ready to pair");
}

void loop() {
  SerialBT.print(chartosend); // Send "Hello, World!" over Bluetooth
  Serial.println(chartosend); // Print confirmation to Serial Monitor
  delay(5000); // Wait 5 seconds before sending again
}

