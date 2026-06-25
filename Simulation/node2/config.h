
// Network
#define NODE_MAC {0xDE, 0xAD, 0xBE, 0xBF, 0xCD, 0xFE}
//ThingsBoard
#define TB_SERVER      "mqtt.eu.thingsboard.cloud"//cloud platform link
#define TB_PORT        1883
#define ACCESS_TOKEN    "Snnio8sHhLKmYCf2mMRy"
#define CLIENT_ID       "Warehouse6956" //name
//MQTT Topic
#define TOPIC_TELEMETRY "v1/devices/me/telemetry"//thingsboard config
#define TOPIC_RPC_RESPONSE "v1/devices/me/rpc/response/"

//time delay
#define TELEMETRY_INTERVAL  5000UL
#define RECONNECT_INTERVAL  5000UL
#define LDR_DARK_THRESH     300

//pins used 
#define DHTTYPE        DHT22
#define DHTPIN          2
#define PIN_PIR         3
#define PIN_RELAY       4
#define PIN_LED_GREEN   5
#define PIN_LED_YELLOW  6
#define PIN_LED_RED     8
#define PIN_DOOR        7
#define PIN_LDR         A0

//sensors config
#define LDR_SAMPLES     4
#define LDR_SAMPLE_DLY  2
#define LDR_DARK_THRESH 300
#define MIN_FREE_SRAM   256

//Thresholds for LED Status
#define TEMP_WARN       28.0f
#define TEMP_CRIT       35.0f
#define HUMIDITY_WARN   70.0f
#define HUMIDITY_CRIT   85.0f
#define MOTION_CLEAR_MS 10000

#define RPC_ID_SIZE     12