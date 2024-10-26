#ifndef PAGEAPPDIAG_H
#define PAGEAPPDIAG_H

#include "GUI/Pages/PageAppBase.h"
#include "GUI/Elements/Composite/TypedNameValue.h"
#include "GUI/Elements/Simple/TypedLabel.h"

class PageAppDiag : public PageAppBase {
protected:
    PercentLabel humidity;
    TemperatureLabel temperature;
    DateLabel date;
    TimeLabel time;

public:
    PageAppDiag() : humidity(2, 12, -1, FontSize::Small),
                    temperature(42, 12, -1, FontSize::Small),
                    date(2, 24, DisplayDate(0,0,0), FontSize::Small), 
                    time(2 + SCREEN_WIDTH / 2, 24, DisplayTime(0,0,0), FontSize::Small) {
        SetTitle("Diagnostics");
        AddElement(&humidity);
        AddElement(&temperature);
        AddElement(&date);
        AddElement(&time);
    }
    
    Pages getType() const override {
        return Pages::Diag;
    }
    
    bool SetHumidity(float newHumidity) {
        humidity.SetValue(newHumidity);
        return true;
    }
    bool SetTemperature(float newTemperature) {
        temperature.SetValue(newTemperature);
        return true;
    }
    bool SetDate(DisplayDate &newDate) {
        date.SetValue(newDate);
        return true;
    }
    bool SetTime(DisplayTime &newTime) {
        time.SetValue(newTime);
        return true;
    }

    bool TickTime() {
        time.Tick();
        return true;
    }
};

#endif // PAGEAPPDIAG_H
