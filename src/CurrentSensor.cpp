#include "CurrentSensor.h"
#include <cstdint>

CurrentSensor::CurrentSensor(int8_t pin, float amplification,
                             float resistenceSensor, float mainVoltage) {
  _pin = pin;
  _amplification = amplification;
  _resistenceSensor = resistenceSensor;
  _mainVoltage = mainVoltage;
}

float CurrentSensor::monitor_current() {

  // analog read voltage from amplifier
  uint16_t adcSensorVal = analogRead(_pin);

  // amplified voltage read on analog pin
  // \[ V_\text{A} = n_\text{adc} / n_\text{max} * 3.3 \si{V} \]
  float voltageAmplified = adcSensorVal / 4095 * 3.3;

  // calculating voltage over shunt
  // \[ V_\text{sens} = V_\text{A}/A \]
  float voltageSensor = voltageAmplified / _amplification;
  // voltageSensor = map(hallEffektValue, 1.5 , 3.5 , -5 , 5); // Mapper værdien

  // calculating current througth sensing resistor
  // \[ I_\text{sens} = V_\text{sens} / R_\text{sens} \]
  float currentSensor = voltageSensor / _resistenceSensor;

  // calculating resistence in of lamp
  // \[ R_\text{lamp} = V_\text{main} / I_{sens} - R_\text{sens} \]
  float resistenceLamp = _mainVoltage / currentSensor; // beregner resistencen

  debug_print(adcSensorVal, voltageAmplified, voltageSensor, currentSensor,
              resistenceLamp);

  return resistenceLamp;
}

void CurrentSensor::debug_print(float adcSensorVal, float voltageAmplified,
                                float voltageSensor, float currentSensor,
                                float resistenceLamp) {

  // Hide curser
  Serial.write(27);
  Serial.print("[?25l");

  // clear screen
  Serial.write(27);
  Serial.print("[2J");

  // write from ( 0 , 0 )
  Serial.write(27);
  Serial.print("[0;0H");

  Serial.print("Adc on pin ");
  Serial.print(_pin);
  Serial.print(" is value: ");
  Serial.write(27);
  Serial.print("[K");                // Down one
  Serial.println(adcSensorVal, DEC); // print as an ASCII-encoded decimal

  Serial.print("Amplified shunt voltage: ");
  Serial.write(27);
  Serial.print("[K");
  Serial.println(voltageAmplified, DEC);

  // From amplified voltage to voltage over sens resistor
  Serial.print("Voltage over shunt: ");
  Serial.write(27);
  Serial.print("[K");
  Serial.println(voltageSensor, DEC);

  // From voltage over sens resistor to current throught the resistor
  Serial.print("Current throught sensor: ");
  Serial.write(27);
  Serial.print("[K");
  Serial.println(currentSensor, DEC);

  // Calculate the total resistence R_sens + R_lamp
  Serial.print("Resistance of Lamp: ");
  Serial.write(27);
  Serial.print("[K");
  Serial.println(resistenceLamp, DEC);
}
