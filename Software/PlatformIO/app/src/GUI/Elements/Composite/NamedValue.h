#ifndef NAMEDVALUE_H
#define NAMEDVALUE_H

#include "GUI/Elements/GuiElement.h"
#include "GUI/Elements/Simple/Label.h"
#include "GUI/Elements/Composite/NamedValueEditState.h"
#include <Arduino.h>

template <typename T>
class NamedValue : public GuiElement {
protected:
    Label<String> nameLabel;
    Label<T> valueLabel;
    NamedValueEditState editState;

public:
    NamedValue(int xPos, int yPos, T initialValue, const String &name, FontSize size = FontSize::Small)
        : NamedValue(xPos, yPos, name, size) {
        SetValue(initialValue);
    }
    NamedValue(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : GuiElement(xPos, yPos),
          nameLabel(xPos, yPos, name),
          valueLabel(xPos + SCREEN_WIDTH / 2, yPos), // Adjust position for the range
          editState(NamedValueEditState::None) {
        nameLabel.SetFontSize(size);
        valueLabel.SetFontSize(size);
    }

    T GetValue() {
        return valueLabel.GetValue();
    }

    void SetValue(T newValue) {
        valueLabel.SetValue(newValue);
    }

    void SetEditState(NamedValueEditState state) {
        editState = state;

        // Set inverted state for labels based on edit state
        if (state == NamedValueEditState::None) {
            nameLabel.SetInverted(false);
            valueLabel.SetInverted(false);
        } else if (state == NamedValueEditState::Selected) {
            nameLabel.SetInverted(true);
            valueLabel.SetInverted(false);
        } else if (state == NamedValueEditState::Entered) {
            nameLabel.SetInverted(true);
            valueLabel.SetInverted(true);
        }
    }

    NamedValueEditState GetEditState() const {
        return editState;
    }

    virtual void Invalidate() override {
        nameLabel.Invalidate();
        valueLabel.Invalidate();
    }

    virtual bool IsInvalidated() const override {
        return (nameLabel.IsInvalidated() || valueLabel.IsInvalidated());
    }

    virtual void Draw(LcdDisplayHandler &displayHandler) override {
        if (!IsInvalidated()) return;

        // Draw name label
        nameLabel.Draw(displayHandler);
        
        // Draw value label
        valueLabel.Draw(displayHandler);
    }
};

#endif // NAMEDVALUE_H
