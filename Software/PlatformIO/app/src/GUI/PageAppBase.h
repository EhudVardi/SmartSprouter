#ifndef PAGEAPPBASE_H
#define PAGEAPPBASE_H

#include "GUI/PageBase.h"
#include "GUI/CenteredLabel.h"
#include "GUI/Line.h"
#include <iostream>

class PageAppBase : public PageBase {
protected:
    CenteredLabel titleLabel;
    Line titleSeparator;

public:
    PageAppBase() : titleLabel(0, "", FontSize::Small), titleSeparator(8) {
        AddElement(&titleLabel);
        AddElement(&titleSeparator);
    }
    
    void SetTitle(String title) {
        titleLabel.UpdateText(title);
    }
};

#endif // PAGEAPPBASE_H
