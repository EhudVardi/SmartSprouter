#ifndef NAMEDVALUE_H
#define NAMEDVALUE_H

#include "GUI/GuiElement.h"
#include "GUI/Label.h"
#include "GUI/NamedValueEditState.h"
#include <Arduino.h>

template <typename T>
class NamedValue : public GuiElement {
private:
    Label nameLabel;
    Label valueLabel;
    T value;
    NamedValueEditState editState;

protected:
    // Virtual function to format the value as a string
    virtual String FormatValue(T value) const {
        return String(value); // Default conversion to string
    }

public:
    NamedValue(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : GuiElement(xPos, yPos),
          nameLabel(xPos, yPos, name, size),
          valueLabel(xPos + SCREEN_WIDTH / 2, yPos, "", size), // Offset for value label
          value(T()), 
          editState(NamedValueEditState::None) {}

    void SetValue(T newValue) {
        value = newValue;
        String strValue = FormatValue(value); // Use the formatting method
        valueLabel.UpdateText(strValue);
        Invalidate();
    }

    T GetValue() const {
        return value;
    }

    void SetEditState(NamedValueEditState state) {
        editState = state;
        Invalidate();

        // Set inverted state for labels based on edit state
        if (state == NamedValueEditState::Selected) {
            nameLabel.SetInverted(true);
            valueLabel.SetInverted(false);
        } else if (state == NamedValueEditState::Entered) {
            nameLabel.SetInverted(false);
            valueLabel.SetInverted(true);
        } else {
            nameLabel.SetInverted(false);
            valueLabel.SetInverted(false);
        }
    }

    NamedValueEditState GetEditState() const {
        return editState;
    }

    virtual void Draw(LcdDisplayHandler &displayHandler) override {
        if (!IsInvalidated()) return;

        // Draw name label
        nameLabel.Draw(displayHandler);

        // Draw value label
        valueLabel.Draw(displayHandler);

        // Clear invalidation flag
        invalidated = false;
    }
};

#endif // NAMEDVALUE_H
