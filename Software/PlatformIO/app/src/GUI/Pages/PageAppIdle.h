#ifndef PAGEAPPIDLE_H
#define PAGEAPPIDLE_H

#include "PageAppBase.h"
#include "GUI/Elements/Composite/TypedNameValue.h"

class PageAppIdle : public PageAppBase {
protected:
    NamedValuePercent humidityGauge;
    NamedValueTemperature temperatureGauge;
    DisplayDateTimeLabel dateTime;

public:
    PageAppIdle() : humidityGauge(2, 12, "Humidity", FontSize::Small),
                    temperatureGauge(2, 24, "Temper'", FontSize::Small), 
                    dateTime(2, 36, AppDateTime(2000,1,1,0,1,2), FontSize::Small) {
        SetTitle("Idle");
        AddElement(&humidityGauge);
        AddElement(&temperatureGauge);
        AddElement(&dateTime);
    }
    
    Pages getType() const override {
        return Pages::Idle;
    }

    bool SetHumidity(float humidityPercent) {
        if (humidityPercent != humidityGauge.GetValue()) {
            if (humidityPercent >= 0.0 &&  humidityPercent <= 100.0) {
                humidityGauge.SetValue(humidityPercent);
                return true;
            }
            else {
                return false;
            }
        }
        return true;
    }

    bool SetTemperature(float temperature) {
        if (temperature != temperatureGauge.GetValue()) {
            if (temperature >= 0.0 &&  temperature <= 100.0) {
                temperatureGauge.SetValue(temperature);
                return true;
            }
            else {
                return false;
            }
        }
        return true;
    }

    bool SetDateTime(const AppDateTime& newDateTime) {
        if (dateTime.GetValue() != newDateTime)
            dateTime.SetValue(newDateTime);
        return true;
    }
};

#endif // PAGEAPPIDLE_H
