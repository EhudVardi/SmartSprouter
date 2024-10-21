#ifndef NAMED_RANGE_H
#define NAMED_RANGE_H

#include "GUI/GuiElement.h"
#include "GUI/Label.h"
#include "GUI/Range.h"
#include "GUI/NamedRangeEditState.h"
#include <Arduino.h>

template <typename T>
class NamedRange : public GuiElement {
protected:
    Label nameLabel;              // The label for the name
    Range<T> valueRange;          // The range for the values
    NamedRangeEditState editState; // Current edit state

public:
    NamedRange(int xPos, int yPos, T initialMinValue, T initialMaxValue, const String &name)
        : NamedRange(xPos, yPos, name) {
        SetMinValue(initialMinValue);
        SetMaxValue(initialMaxValue);
    }
    NamedRange(int xPos, int yPos, const String &name)
        : GuiElement(xPos, yPos),
          nameLabel(xPos, yPos, name),
          valueRange(xPos + SCREEN_WIDTH * 3 / 8, yPos), // Adjust position for the range
          editState(NamedRangeEditState::None) {
        // Set the initial sizes of the elements
        //valueRange.SetSize(100, 16); // Assuming 100x16 for the range display, adjust as necessary
    }

    // Getters for min and max values
    T GetMinValue() {
        return valueRange.GetMinValue();
    }
    T GetMaxValue() {
        return valueRange.GetMaxValue();
    }

    // Setters for min and max values
    void SetMinValue(T newMinValue) {
        valueRange.SetMinValue(newMinValue);
    }

    void SetMaxValue(T newMaxValue) {
        valueRange.SetMaxValue(newMaxValue);
    }

    // Set and get the edit state
    void SetEditState(NamedRangeEditState state) {
        editState = state;
        if (state == NamedRangeEditState::None) {
            nameLabel.SetInverted(false);
            valueRange.SetMinInverted(false);
            valueRange.SetMaxInverted(false);
        } else if (state == NamedRangeEditState::Selected) {
            nameLabel.SetInverted(true);
            valueRange.SetMinInverted(false);
            valueRange.SetMaxInverted(false);
        } else if (state == NamedRangeEditState::EnteredMin) {
            nameLabel.SetInverted(true);
            valueRange.SetMinInverted(true);
            valueRange.SetMaxInverted(false);
        } else if (state == NamedRangeEditState::EnteredMax) {
            nameLabel.SetInverted(true);
            valueRange.SetMinInverted(false);
            valueRange.SetMaxInverted(true);
        }
    }

    NamedRangeEditState GetEditState() const {
        return editState;
    }

    virtual void Invalidate() override {
        nameLabel.Invalidate();
        valueRange.Invalidate();
    }

    virtual bool IsInvalidated() const override {
        return (nameLabel.IsInvalidated() || valueRange.IsInvalidated());
    }

    // Override the Draw function
    virtual void Draw(LcdDisplayHandler &displayHandler) override {
        if (!IsInvalidated()) return;

        // Draw the name label
        nameLabel.Draw(displayHandler);

        // Draw the value range
        valueRange.Draw(displayHandler);
    }
};

#endif // NAMED_RANGE_H
