#ifndef PAGEAPPABORT_H
#define PAGEAPPABORT_H

#include "GUI/Pages/PageAppBase.h"
#include "GUI/Elements/Simple/TypedLabel.h"

class PageAppAbort : public PageAppBase {
protected:
    CenteredLabel confirmQuestion;
    CenteredLabel confirmInsrtruction;

public:
    PageAppAbort() : confirmQuestion(SCREEN_HEIGHT / 4 + 6, "R U Sure?", FontSize::Medium), 
                     confirmInsrtruction(SCREEN_HEIGHT / 4 + 30, "Enter To Confirm", FontSize::Small) {
        SetTitle("Abort");
        AddElement(&confirmQuestion);
        AddElement(&confirmInsrtruction);
    }
    
    Pages getType() const override {
        return Pages::Abort;
    }
};

#endif // PAGEAPPABORT_H
