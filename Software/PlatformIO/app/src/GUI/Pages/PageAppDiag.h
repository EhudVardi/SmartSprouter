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
    DateTimeLabel dateTime;
    NamedValueHumidifierActions humidifiers;

public:
    PageAppDiag() : humidity(2, 12, -1, FontSize::Small),
                    temperature(42, 12, -1, FontSize::Small),
                    dateTime(2, 22, DateTime(2000,1,1,0,1,2), FontSize::Small),
                    humidifiers(2, 32, HumidifierActions::Off, "Humidifiers", FontSize::Small) {
        SetTitle("Diagnostics");
        AddElement(&humidity);
        AddElement(&temperature);
        AddElement(&dateTime);
        AddElement(&humidifiers);
    }
    
    Pages getType() const override {
        return Pages::Diag;
    }
    
    bool SetHumidity(float newHumidity) {
        if (newHumidity != humidity.GetValue())
            humidity.SetValue(newHumidity);
        return true;
    }
    bool SetTemperature(float newTemperature) {
        if (newTemperature != temperature.GetValue())
            temperature.SetValue(newTemperature);
        return true;
    }
    bool SetDateTime(const DateTime& newDateTime) {
        if (dateTime.GetValue() != newDateTime)
            dateTime.SetValue(newDateTime);
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
