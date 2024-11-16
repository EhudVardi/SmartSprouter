#ifndef NAMED_RANGE_H
#define NAMED_RANGE_H

#include <Arduino.h>
#include "GUI/Elements/GuiElement.h"
#include "GUI/Elements/Simple/Label.h"
#include "GUI/Elements/Simple/Range.h"
#include "NamedRangeEditState.h"

template <typename T>
class NamedRange : public GuiElement {
protected:
    TextLabel nameLabel;
    Range<T> valueRange;
    NamedRangeEditState editState;

public:
    NamedRange(int xPos, int yPos, T initialMinValue, T initialMaxValue, const String& name)
        : NamedRange(xPos, yPos, name) {
        SetMinValue(initialMinValue);
        SetMaxValue(initialMaxValue);
    }
    NamedRange(int xPos, int yPos, const String& name)
        : GuiElement(xPos, yPos),
        nameLabel(xPos, yPos, name),
        valueRange(xPos + SCREEN_WIDTH * 3 / 8, yPos),
        editState(NamedRangeEditState::None) {
    }

    T GetMinValue() {
        return valueRange.GetMinValue();
    }
    T GetMaxValue() {
        return valueRange.GetMaxValue();
    }

    void SetMinValue(T newMinValue) {
        valueRange.SetMinValue(newMinValue);
    }

    void SetMaxValue(T newMaxValue) {
        valueRange.SetMaxValue(newMaxValue);
    }

    void SetEditState(NamedRangeEditState state) {
        editState = state;
        if (state == NamedRangeEditState::None) {
            nameLabel.SetInverted(false);
            valueRange.SetMinInverted(false);
            valueRange.SetMaxInverted(false);
        }
        else if (state == NamedRangeEditState::Selected) {
            nameLabel.SetInverted(true);
            valueRange.SetMinInverted(false);
            valueRange.SetMaxInverted(false);
        }
        else if (state == NamedRangeEditState::EnteredMin) {
            nameLabel.SetInverted(true);
            valueRange.SetMinInverted(true);
            valueRange.SetMaxInverted(false);
        }
        else if (state == NamedRangeEditState::EnteredMax) {
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

    virtual void Draw(LcdDisplayHandler& displayHandler) override {
        if (!IsInvalidated()) return;

        nameLabel.Draw(displayHandler);
        valueRange.Draw(displayHandler);
    }
};

#endif // NAMED_RANGE_H
