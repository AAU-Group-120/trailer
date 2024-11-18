#ifndef currentsensor_h
#define currentsensor_h
#include "Arduino.h"
#include <cstdint>

class CurrentSensor {
public:
  CurrentSensor(unsigned char wire, int8_t pinSensor, int8_t pinInput,
                int8_t pinDebugLED, float amplification, float resistenceSensor,
                float mainVoltage);
  unsigned char monitor_current();
  /* void on(); */

private:
  unsigned char _wire;
  int8_t _pinSensor;
  int8_t _pinInput;
  int8_t _pinDebugLED;
  float _amplification;
  float _resistenceSensor;
  float _mainVoltage;
  void debug_print(float adcSensorVal, float voltageAmplified,
                   float voltageSensor, float currentSensor,
                   float resistenceLamp);

  void led_on();
  void led_off();
};

#endif // CURRENTSENSOR_H_
