#ifndef ACTUATORS_H
#define ACTUATORS_H


#include <Arduino.h>
#include "config.h"

void actuators_begin(void);
void actuators_setRelay(uint8_t);
uint8_t actuators_getRelayState(void);
uint8_t actuators_setLED(uint8_t pin,uint8_t on);
void actuators_updateStatusLEDs(uint8_t mqttConnected, uint8_t sensorError);

#endif /*ACTUATORS_H*/