#ifndef PAGEAPPBASE_H
#define PAGEAPPBASE_H

#include "GUI/PageBase.h"
#include "GUI/CenteredLabel.h"
#include <iostream>

class PageAppBase : public PageBase {
protected:
    CenteredLabel titleLabel;

public:
    PageAppBase() : titleLabel(0, "", FontSize::Small) {
        AddElement(&titleLabel);
    }
    
    void SetTitle(String title) {
        titleLabel.UpdateText(title);
    }
};

#endif // PAGEAPPBASE_H
