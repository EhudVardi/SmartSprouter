#ifndef PAGEAPPBASE_H
#define PAGEAPPBASE_H

#include "GUI/Pages/PageBase.h"
#include "GUI/Elements/Simple/CenteredLabel.h"
#include "GUI/Elements/GFX/Line.h"

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
    
    void SetTitle(String title) {
        titleLabel.UpdateText(title);
    }
};

#endif // PAGEAPPBASE_H
