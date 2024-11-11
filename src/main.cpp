#include "Arduino.h"
#include "HardwareSerial.h"
#include "stdint.h"
#include "BluetoothSerial.h"

// Overvej at lav en address, ellers vil koden kunne spores til alle bluetooth enheder og ikke kun det ønskede mål
// For nu, nøjes vi dog med, at se det som en ekstra indskydning, men holder reciveren til at finde transmitteren

char chartosend = '1';

int fejl = 2;




BluetoothSerial SerialBT;     // Create a Bluetooth Serial object
void setup() {
  Serial.begin(115200);        // Initialize serial monitor
  SerialBT.begin("ESP32_Transmitter"); // Set Bluetooth name to "ESP32_Transmitter"
  Serial.println("Bluetooth Device is ready to pair");
}

void message(int fejl){
  switch (fejl)
  {
  case 1: SerialBT.print("fejl 1"); Serial.println("fejl 1"); break; //Fejl 1 is being sent via bluetooth
  case 2: SerialBT.print("fejl 2"); Serial.println("fejl 2"); break;

  default:
    break;
  }
}


void loop() {
  message(fejl);
  delay(5000); // Wait 5 seconds before sending again

}




