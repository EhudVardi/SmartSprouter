#ifndef PAGEAPPBASE_H
#define PAGEAPPBASE_H

#include "GUI/Pages/PageBase.h"
#include "GUI/Elements/GFX/Line.h"
#include "GUI/Elements/Simple/TypedLabel.h"

class PageAppBase : public PageBase {
protected:
    CenteredLabel titleLabel;
    Line titleSeparator;

public:
    PageAppBase() : titleLabel(0, "", FontSize::Small), titleSeparator(8) {
        AddElement(&titleLabel);
        AddElement(&titleSeparator);
    }
    
    virtual Pages getType() const override = 0;
    
    void SetTitle(const String& title) {
        titleLabel.SetValue(title);
    }
};

#endif // PAGEAPPBASE_H
