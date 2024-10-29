#ifndef PAGEAPPIDLE_H
#define PAGEAPPIDLE_H

#include "GUI/Pages/PageAppBase.h"
#include "GUI/Elements/Composite/TypedNameValue.h"

class PageAppIdle : public PageAppBase {
protected:
    NamedValuePercent humidityGauge;
    NamedValueTemperature temperatureGauge;
    DateTimeLabel dateTime;

public:
    PageAppIdle() : humidityGauge(2, 12, "Humidity", FontSize::Small),
                    temperatureGauge(2, 24, "Temper'", FontSize::Small), 
                    dateTime(2, 36, DateTime(2000,1,1,0,1,2), FontSize::Small) {
        SetTitle("Idle");
        AddElement(&humidityGauge);
        AddElement(&temperatureGauge);
        AddElement(&dateTime);
    }
    
    Pages getType() const override {
        return Pages::Idle;
    }

    bool SetHumidity(float humidityPercent) {
        if (humidityPercent >= 0.0 &&  humidityPercent <= 100.0) {
            humidityGauge.SetValue(humidityPercent);
            return true;
        }
        else {
            return false;
        }
    }

    bool SetTemperature(float temperature) {
        if (temperature >= 0.0 &&  temperature <= 100.0) {
            temperatureGauge.SetValue(temperature);
            return true;
        }
        else {
            return false;
        }
    }
};

#endif // PAGEAPPIDLE_H
