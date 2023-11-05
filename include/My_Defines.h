#define DEVICE_NAME         "Gulliver"
#define DEVICE_ID           1   // Mudar para cada dispositivo
#define FW_REVISION         "R1"		// Same as FW_VERSION, but string type
#define FW_VERSION          1

#define DEVICE_NAME_BL      String(DEVICE_NAME) + "_" + String(DEVICE_ID) // Nome da conexão BL
#define MAC_CONTROLLER      "4c:b9:9b:60:58:9d" //Endereço BL do contorle

//********* WIFI **************
#define SSID "BUSCAPE"
#define PASS "luaetrovao01"
//********* PINS **************
#define LED_RED 14
#define LED_GREEN 12
#define LED_BLUE 13

#define BUTTON_PIN 23

#define MOTOR1_PIN1 5
#define MOTOR1_PIN2 21

#define MOTOR1_PIN3 19
#define MOTOR1_PIN4 18

#define MOTOR2_PIN1 2
#define MOTOR2_PIN2 4

#define MOTOR2_PIN3 32
#define MOTOR2_PIN4 33


#define PROCESSOR_COMMUNICATION 1
#define PROCESSOR_MAIN 0

//********* WIFI **************
#define WIFI_DISABLE 0       // WiFi disabled (Off)
#define WIFI_ST_MODE 1       // Entering in WiFi mode as client
#define WIFI_SERVER_ENABLE 2 // Entering in WiFi mode as server
#define WIFI_CLIENT_INIT 3   // Initialize WiFi mode as client
#define WIFI_SERVER_INIT 4   // Initialize WiFi mode as server
#define WIFI_INIT_ST_MODE 5  // Connecting in the WiFi net
#define WIFI_INIT_AP_MODE 6  // Entering in WiFi AP mode
#define WIFI_AP_RUNNING 7    // Running in WiFi mode (On)

//********* TIMERs **************

#define TIMER_BL 1000