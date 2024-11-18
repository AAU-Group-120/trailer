#include "CurrentSensor.h"
#include "esp32-hal-gpio.h"
#include <cstdint>

CurrentSensor::CurrentSensor(unsigned char wire, int8_t pinSensor,
                             int8_t pinInput, int8_t pinDebugLED,
                             float amplification, float resistenceSensor,
                             float mainVoltage) {
  _wire = wire;
  _pinSensor = pinSensor;
  _pinInput = pinInput;
  _pinDebugLED = pinDebugLED;
  _amplification = amplification;
  _resistenceSensor = resistenceSensor;
  _mainVoltage = mainVoltage;

  pinMode(_pinInput, INPUT_PULLDOWN);
  pinMode(_pinDebugLED, OUTPUT);
}

unsigned char CurrentSensor::monitor_current() {

  if (digitalRead(_pinInput)) {
    if (CurrentSensor::monitor_current_internal() > 100.0) {
      CurrentSensor::led_on();
      return _wire;
    } else {
      CurrentSensor::led_off();
      return 0b0;
    }
  } else {
    CurrentSensor::led_off();
    return 0b0;
  }
}

float CurrentSensor::monitor_current_internal() {

  // analog read voltage from amplifier
  uint16_t adcSensorVal = analogRead(_pinSensor);

  // amplified voltage read on analog pin
  // \[ V_\text{A} = n_\text{adc} / n_\text{max} * 3.3 \si{V} \]
  float voltageAmplified = adcSensorVal / (float)4095 * 3.3;

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
  Serial.print(_pinSensor);
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

void CurrentSensor::led_on() { digitalWrite(_pinDebugLED, HIGH); }

void CurrentSensor::led_off() { digitalWrite(_pinDebugLED, LOW); }
