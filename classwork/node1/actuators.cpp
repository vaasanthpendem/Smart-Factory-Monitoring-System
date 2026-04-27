#include "actuators.h"
static uint8_t bState=0;
static unsigned long lastBlinkTime=0;
static uint8_t relayStatus;

void actuators_begin(void){
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_RELAY, OUTPUT);
  //in the beginning till the RED led is on
  digitalWrite(PIN_LED_RED, HIGH);
}

//from RPC request to set relay then turn ON relay
void actuators_setRelay(uint8_t on){
  relayStatus=on;
digitalWrite(PIN_RELAY,on? HIGH:LOW);

}

//send back the status of relay to Things Board
uint8_t actuators_getRelayState(void){
  return relayStatus;
}

void actuators_updateStatusLEDs(uint8_t mqttConnected, uint8_t sensorError){
  //if board is not connected to cloud then turn on RED LED
  if(!mqttConnected){
    digitalWrite(PIN_LED_RED,HIGH);
    digitalWrite(PIN_LED_YELLOW,LOW);
    digitalWrite(PIN_LED_GREEN,LOW);
    return;
  }
  //if mqtt is on, turn off RED LED
  digitalWrite(PIN_LED_RED,LOW);
  //if sensor error then turn on YELLOW LED
  if(sensorError){
    digitalWrite(PIN_LED_YELLOW,HIGH);
    unsigned long now=millis();
    if(now-lastBlinkTime>500){
        lastBlinkTime=now;
        bState=!bState;
        digitalWrite(PIN_LED_YELLOW, bState? HIGH: LOW);
      }
    }
    else{
      digitalWrite(PIN_LED_GREEN,HIGH);
      digitalWrite(PIN_LED_YELLOW,LOW);
    }
  
  //If everything is normal turn on GREEN LED

}