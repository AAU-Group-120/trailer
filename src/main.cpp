#include "Arduino.h"
#include "HardwareSerial.h"
#include "stdint.h"
#include "BluetoothSerial.h"

// Overvej at lav en address, ellers vil koden kunne spores til alle bluetooth enheder og ikke kun det ønskede mål
// For nu, nøjes vi dog med, at se det som en ekstra indskydning, men holder reciveren til at finde transmitteren



unsigned char fejl = 0b0000001;
int tidligerFejl = 0;
uint32_t i=0;

BluetoothSerial SerialBT;     // Create a Bluetooth Serial object
void setup() {
  Serial.begin(115200);        // Initialize serial monitor
  SerialBT.begin("ESP32_Transmitter"); // Set Bluetooth name to "ESP32_Transmitter"
  Serial.println("Bluetooth Device is ready to pair");
}

void loop() {
  //message(fejl);
  //delay(1000); // Wait 30 seconds before sending again
  if (fejl !=  tidligerFejl){
    tidligerFejl = fejl;
    SerialBT.print(fejl);
    Serial.println(fejl);
  }

  i++;
  if (i>1800000){
    fejl = (fejl+1)%64;
    i = 0;
  }




}






