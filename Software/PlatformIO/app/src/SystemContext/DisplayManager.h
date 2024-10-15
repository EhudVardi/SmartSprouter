#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include "BaseManager.h"
#include <string>

class DisplayManager : public BaseManager {
public:
    bool initialize() override;
    void showPage(const std::string& page);
    void updateLabel(const std::string& label, const std::string& value);
};

#endif // DISPLAY_MANAGER_H
