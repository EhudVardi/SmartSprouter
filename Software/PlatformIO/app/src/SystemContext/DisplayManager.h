#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <string>

class DisplayManager {
public:
    void showPage(const std::string& page);
    void updateLabel(const std::string& label, const std::string& value);
};

#endif // DISPLAY_MANAGER_H
