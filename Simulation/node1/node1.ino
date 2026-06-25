#include<SPI.h>
#include<Ethernet.h>
#include<PubSubClient.h>
#include<DHT.h>

#include "config.h"
#include "sensorsManager.h"
#include "actuators.h"
#include "telemetry.h"
#include "network.h"
#include "rpc.h"

//Object of ethernet and pubsubclient
static EthernetClient ethCl;
static PubSubClient mqttCl(ethCl);
unsigned long lastTelemetry=0;
static char sharedBuf[200];

void setup() {
  Serial.begin(9600);
  Serial.print("Node1 is booting...");
  // put your setup code here, to run once:
  //initialise the sensors 
  sensor_begin();
  //initialise the actuators
 actuators_begin();

  telemetry_init(sharedBuf,sizeof(sharedBuf));
  rpc_init(&mqttCl,sharedBuf,sizeof(sharedBuf));
  mqttCl.setCallback(rpc_mqttCallback);
  //connect the board to internet and mqtt
  network_begin(&mqttCl);
  mqttCl.setCallback(rpc_mqttCallback);

  digitalWrite(PIN_LED_RED,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  //check the connection of UNO to ThingsBoard
  network_maintain();

  //read the data from sensors
  SensorData data; //object of structure
  sensors_read(&data);
  //publish this data in cloud
  //check if network is available then push the data to cloud
  if(network_isConnected()){
    //publish data to thingsboard at every 5 sec
    unsigned long now=millis();
    if(now-lastTelemetry>=TELEMETRY_INTERVAL){ //checking the time gap as 5
      lastTelemetry=now;
      telemetry_publishTelemetry(&data,actuators_getRelayState); //sensor data into JSON and publish
    }
  }
  actuators_updateStatusLEDs(network_isConnected(),data.sensorError);
}
