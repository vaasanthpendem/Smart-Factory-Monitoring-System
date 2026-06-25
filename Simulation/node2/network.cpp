#include "network.h"
#include "config.h"
static PubSubClient* mqtt=NULL;
static byte  mac[6]=NODE_MAC;
static unsigned long lastReconnectTime=0;

static void doConnect(void){
  if(mqtt->connect(CLIENT_ID,ACCESS_TOKEN,NULL)){ //NULL is password for ClientId here,but can be changed
    Serial.print("connected!");
  }else{
    Serial.print("MQTT failed :(");
  }
}

void network_maintain(void){
  Ethernet.maintain();
  
  if(mqtt->connected()){
    mqtt->loop();
  }else{
    unsigned long now=millis();
    if(now-lastReconnectTime >= RECONNECT_INTERVAL){
      lastReconnectTime=now;
      doConnect();
    }
  }
  
}


void network_begin(PubSubClient* mqttCl){
  mqtt=mqttCl;
  //connect board to internet 
  Ethernet.begin(mac);
  delay(2000);
  //connect to thingsboard
  mqtt->setServer(TB_SERVER, TB_PORT);
  doConnect();
}

uint8_t network_isConnected(void){
  return (uint8_t) mqtt->connected();
}

uint8_t network_publish(const char* topic,const char* payload,uint8_t retain){
  return (uint8_t) mqtt->publish(topic,payload), (bool)retain;

}