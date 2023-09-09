#define DEVICE_NAME         "Gulliver"
#define DEVICE_ID           1   // Mudar para cada dispositivo
#define FW_REVISION         "R1"		// Same as FW_VERSION, but string type
#define FW_VERSION          1

#define DEVICE_NAME_BL         String(DEVICE_NAME) + "_" + String(DEVICE_ID)
#define PS3_KEY             "5c:6d:20:07:55:21"

//********* BLYNK **************
#define BLYNK_TEMPLATE_ID "TMPL2yI3kdDCD"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "7Bnx6qLS4MxJx8ukbOCZdjH0fJq3Vevd"
//********* WIFI **************
#define SSID "BUSCAPE"
#define PASS "luaetrovao01"
//********* PINS **************
#define PIN_LED 2

#define BUTTON_PIN 23

#define PROCESSOR_COMMUNICATION 1
#define PROCESSOR_MAIN 0

// WIFI
#define WIFI_DISABLE 0       // WiFi disabled (Off)
#define WIFI_ST_MODE 1       // Entering in WiFi mode as client
#define WIFI_SERVER_ENABLE 2 // Entering in WiFi mode as server
#define WIFI_CLIENT_INIT 3   // Initialize WiFi mode as client
#define WIFI_SERVER_INIT 4   // Initialize WiFi mode as server
#define WIFI_INIT_ST_MODE 5  // Connecting in the WiFi net
#define WIFI_INIT_AP_MODE 6  // Entering in WiFi AP mode
#define WIFI_AP_RUNNING 7    // Running in WiFi mode (On)
