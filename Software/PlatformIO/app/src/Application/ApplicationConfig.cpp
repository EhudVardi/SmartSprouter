#include "ApplicationConfig.h"

//DEFAULTS
const float DEFAULT_HUMIDITY_RANGE_SETUP_MIN = 65.0; // default humidity range setup min percent (65%)
const float DEFAULT_HUMIDITY_RANGE_SETUP_MAX = 75.0; // default humidity range setup max percent (75%)
const float DEFAULT_TEMPERATURE_RANGE_SETUP_MIN = 22.0; // default temperature range setup min celsius (22.0C)
const float DEFAULT_TEMPERATURE_RANGE_SETUP_MAX = 28.0; // default temperature range setup max celsius (28.0C)
const AppTimeSpan DEFAULT_DURATION_SETUP(3, 0, 0, 0); // default process total duration range setup max celsius (3 days)

//TIME
const int UTC_OFFSET_HOURS = 2; // utc offset (+2HR)

//STORAGE
const int STORE_PROCESS_INTERVAL = 10000; //store process state every 10 seconds

//NETWORK
const char* LAN_SSID = "SSID";
const char* LAN_PASS = "PASSWORD";
const char* NTP_SERVER_URL = "pool.ntp.org";
const int NTP_SERVICE_PORT = 123;