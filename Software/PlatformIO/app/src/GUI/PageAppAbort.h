#ifndef PAGEAPPABORT_H
#define PAGEAPPABORT_H

#include "GUI/PageAppBase.h"
#include "GUI/CenteredLabel.h"

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
};

#endif // PAGEAPPABORT_H
