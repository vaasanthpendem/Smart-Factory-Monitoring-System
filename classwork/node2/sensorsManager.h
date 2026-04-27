#ifndef SENSORS_MANAGER_H
#define SENSORS_MANAGER_H

/*
 * sensors.h — reads DHT22, LDR, and button.
 *
 * C-style module: all state lives in static globals inside sensors.cpp.
 * Call sensors_begin() once in setup(), then sensors_read() in loop().
 */

#include <Arduino.h>
#include "config.h"

typedef struct{
    float temperature;
    float humidity;
    uint8_t ldrValue;
    bool motionDetected;
    bool doorOpen;
    bool isDark;
    bool sensorError;
}SensorData;

typedef struct{
    float lastTemp;
    float lastHumidity;
    bool motionActive;
    unsigned long motionClearTime;
}SensorManager;

void sensorMgr_init(SensorManager* sm);
void sensor_begin(void);
bool sensorMgr_read( SensorData* out,SensorManager* sm);
int  sensorMgr_freeMemory(void);

#endif /* SENSOR_MANAGER_H */
