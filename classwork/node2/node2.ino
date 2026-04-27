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
static SensorManager sm;


void setup() {
  Serial.begin(9600);
  Serial.print("Node2 is booting...");

  // put your setup code here, to run once:
  //initialise the sensors 
  sensor_begin();
  sensorMgr_init(&sm);
  //initialise the actuators
 actuators_begin();

  telemetry_init(sharedBuf,sizeof(sharedBuf));
  rpc_init(&mqttCl,sharedBuf,sizeof(sharedBuf));
  //connect the board to internet and mqtt
  network_begin(&mqttCl);

 
}

void loop() {
  // put your main code here, to run repeatedly:
  //check the connection of UNO to ThingsBoard
  network_maintain();

  //read the data from sensors
  SensorData data; //object of structure
  sensorMgr_read(&data,&sm); //humidity, temp,ldr,door status, motion status

  //if humidity is more than 85 turn on the relay if relay is off
  if(data.humidity>=HUMIDITY_CRIT && !actuators_getRelayState()){
    actuators_setRelay(1);
  }

  //publish this data in cloud
  //check if network is available then push the data to cloud
  if(network_isConnected()){
    //publish data to thingsboard at every 5 sec
    unsigned long now=millis();
    if(now-lastTelemetry>=TELEMETRY_INTERVAL){ //checking the time gap as 5
      lastTelemetry=now;
      telemetry_publishTelemetry(&data,1); //sensor data into JSON and publish
    }
  }
  actuators_updateStatusLEDs(network_isConnected(),data.sensorError);
}
