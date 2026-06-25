#include "sensorsManager.h"
#include "config.h"
#include <DHT.h>

static DHT dht(DHTPIN, DHTTYPE);
static float lastTemp,lastHumidity;


void sensor_begin(void){
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  dht.begin();
}

//read vibration from POT
static uint16_t readVibration(void){
  uint16_t sum=0;
  uint8_t i;
  for(i=0;i<4;i++){
    sum+=analogRead(PIN_VIBRATION);
    delay(100);

  }
  return sum/4; //average of 4 samples

}
//read LM35 Temperature
static float readLM35(void){
  //LM35 gives the voltage we need to convert it into thr temperature 
  //10mV rise in every 1 degree temperature rise 

  float t=analogRead(PIN_LM35)*(500.0f/1023.0f);
  return round(t*10.0f)*0.1f;
}

//reading the data from the sensor and return the status on error as 0
uint8_t sensors_read(SensorData* out){
  //read DHT22
  float t= dht.readTemperature();
  float h=dht.readHumidity();
  //check the error in reading 
  if(isnan(t)||isnan(h)){
    out->sensorError=1;
    out->temperature=lastTemp;
    out->humidity=lastHumidity;

  }else{
    out->sensorError=0;
    out->temperature=round(t*10.0f)*0.1f;
    out->humidity=round(h*10.0f)*0.1f;
    //for storing the previous values
    lastTemp=out->temperature;
    lastHumidity=out->humidity;
  }

  //read the vibration, lm35 Reading and status of machine
  out->lm35Temp=readLM35();
  out->vibration=readVibration();
  out->machineStatus=(digitalRead(PIN_BUTTON)==LOW)?1:0;
  return !out->sensorError;
}

