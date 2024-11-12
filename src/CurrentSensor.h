#ifndef currentsensor_h
#define currentsensor_h
#include "Arduino.h"
#include <cstdint>

class CurrentSensor {
public:
  CurrentSensor(int8_t pin, float amplification, float resistenceSensor,
                float mainVoltage);
  float monitor_current();
  /* void on(); */

private:
  int8_t _pin;
  float _amplification;
  float _resistenceSensor;
  float _mainVoltage;
  void debug_print(float adcSensorVal, float voltageAmplified,
                   float voltageSensor, float currentSensor,
                   float resistenceLamp);
};

#endif // CURRENTSENSOR_H_
