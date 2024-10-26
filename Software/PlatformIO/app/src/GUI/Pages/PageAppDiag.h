#ifndef PAGEAPPDIAG_H
#define PAGEAPPDIAG_H

#include "GUI/Pages/PageAppBase.h"
#include "GUI/Elements/Composite/TypedNameValue.h"
#include "GUI/Elements/Simple/TypedLabel.h"
#include "SystemContext/SystemManagers/ActuatorActions.h"

class PageAppDiag : public PageAppBase {
protected:
    PercentLabel humidity;
    TemperatureLabel temperature;
    DateLabel date;
    TimeLabel time;
    NamedValueHumidifierActions humidifiers;

public:
    PageAppDiag() : humidity(2, 12, -1, FontSize::Small),
                    temperature(42, 12, -1, FontSize::Small),
                    date(2, 22, DisplayDate(0,0,0), FontSize::Small), 
                    time(2 + SCREEN_WIDTH / 2, 22, DisplayTime(0,0,0), FontSize::Small),
                    humidifiers(2, 32, HumidifierActions::Off, "Humidifiers", FontSize::Small) {
        SetTitle("Diagnostics");
        AddElement(&humidity);
        AddElement(&temperature);
        AddElement(&date);
        AddElement(&time);
        AddElement(&humidifiers);
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
    
    void SelectNextHumidifierAction() { humidifiers.SelectNextValue(); }
    void SelectPrevHumidifierAction() { humidifiers.SelectPrevValue(); }
    void SetSelectedHumidifierAction(HumidifierActions newAction) { humidifiers.SetValue(newAction); }
    HumidifierActions GetSelectedHumidifierAction() { return humidifiers.GetValue(); }

    void SetHumidifiersEditState(NamedValueEditState newState) {
        humidifiers.SetEditState(newState);
    }
};

#endif // PAGEAPPDIAG_H
