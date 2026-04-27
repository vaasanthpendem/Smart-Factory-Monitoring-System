#include "sensorsManager.h"
#include "config.h"
#include <DHT.h>

static DHT dht(DHTPIN, DHTTYPE);

void sensorMgr_init(SensorManager* sm){
  sm->lastTemp=0.0f;
  sm->lastHumidity=0.0f;
  sm->motionActive=false;
  sm->motionClearTime=0;

}


void sensor_begin(void){
  pinMode(PIN_PIR, INPUT);
  pinMode(PIN_DOOR,INPUT_PULLUP);

  dht.begin();
}

//read sensor of PIR
static bool readPIR(SensorManager* sm){
  //read the value from motion sensor, if it is true for next 10 sec implies motion
  const bool pirHigh=(digitalRead(PIN_PIR)==HIGH);
  const unsigned long now=millis();
  if(pirHigh){
    sm->motionActive=true;
    sm->motionClearTime=now+MOTION_CLEAR_MS;
  }else if(sm->motionActive && (now >= sm->motionClearTime)){
    sm->motionActive=false;
  }
  return sm->motionActive;//1 if the motion is detected
}

//read door status
static bool readDoor(void){
  return (digitalRead(PIN_DOOR)==LOW); //0 door is open, 1 if door is closed
}

//read LDR sensor - returns the warehouse is dark or not
static uint16_t readLDR(void){
  uint16_t sum=0;
  uint8_t i=0;
  for(i;i<4;i++){
    sum+=(uint16_t)analogRead(PIN_LDR);
    delay(2); //2ms delay
  }
  return sum/4;
}


//reading the data from the sensor and return the status on error as 0
bool sensorMgr_read(SensorData* out,SensorManager* sm){
  //read DHT22
  float t= dht.readTemperature();
  float h=dht.readHumidity();
  //check the error in reading 
  if(isnan(t)||isnan(h)){
    out->sensorError=1;
    out->temperature=sm->lastTemp;
    out->humidity=sm->lastHumidity;

  }else{
    out->sensorError=0;
    out->temperature=round(t*10.0f)*0.1f;
    out->humidity=round(h*10.0f)*0.1f;
    //for storing the previous values
    sm->lastTemp=out->temperature;
    sm->lastHumidity=out->humidity;
  }

  //read the LDR data, door status, motion detection
  out->motionDetected=readPIR(sm);
  out->doorOpen=readDoor();
  out->ldrValue=readLDR();
  out->isDark=(out->ldrValue<LDR_DARK_THRESH);

  return !out->sensorError;
}

