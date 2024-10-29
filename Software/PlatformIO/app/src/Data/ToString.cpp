#include "Data/ToString.h"

String dateTimeToArduinoString(const DateTime& dt) {
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d:%02d", 
             dt.year(), dt.month(), dt.day(), dt.hour(), dt.minute(), dt.second());
    return String(buffer);
}