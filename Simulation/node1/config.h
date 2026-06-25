
// Network
#define NODE_MAC {0xDE, 0xAD, 0xBE, 0xBF, 0xCD, 0xFE}
//ThingsBoard
#define TB_SERVER      "mqtt.eu.thingsboard.cloud"
#define TB_PORT        1883
#define ACCESS_TOKEN    "mTyeyR2YgTT9C8zIYVi6"
#define CLIENT_ID       "Connekt6956"
//MQTT Topic
#define TOPIC_TELEMETRY "v1/devices/me/telemetry"
#define TOPIC_RPC_REQUEST "v1/devices/me/rpc/request/+" //subscribing the topic
#define TOPIC_RPC_RESPONSE "v1/devices/me/rpc/response/" //
//time delay
#define TELEMETRY_INTERVAL  5000UL
#define RECONNECT_INTERVAL  5000UL

//pins used 
#define DHTTYPE        DHT22
#define DHTPIN         2
#define PIN_BUTTON      3
#define PIN_LED_GREEN   5
#define PIN_LED_YELLOW  6
#define PIN_LED_RED     7
#define PIN_RELAY       4
#define PIN_VIBRATION   A0
#define PIN_LM35        A1 

#define RPC_ID_SIZE     12