#include "Application/ApplicationConfig.h"

//DEFAULTS
const float def_humidityRangeSetupMin = 65.0; // default humidity range setup min percent (65%)
const float def_humidityRangeSetupMax = 75.0; // default humidity range setup max percent (75%)
const float def_temperatureRangeSetupMin = 22.0; // default temperature range setup min celsius (22.0C)
const float def_temperatureRangeSetupMax = 28.0; // default temperature range setup max celsius (28.0C)
const DisplayTimeSpan def_durationSetup(3,0,0,0); // default process total duration range setup max celsius (3 days)

//TIME
const int utcOffsetHours = 2; // utc offset (+2HR)

//NETWORK
const char* ssid = "SSID";
const char* password = "PASSWORD";
const char* ntpServerUrl = "pool.ntp.org";
const int ntpPort = 123;