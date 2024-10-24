#ifndef PAGES_ENUMERATION_H
#define PAGES_ENUMERATION_H

#include <unordered_map>
#include <string>

enum class Pages {
    About,
    Idle,
    Setup,
    Run,
    Abort,
    Error,
};

// Use a static map to convert enums to strings
inline const char* Pages_ToString(Pages s) {
    static const std::unordered_map<Pages, const char*> pagesMap = {
        { Pages::About, "About" },
        { Pages::Idle, "Idle" },
        { Pages::Setup, "Setup" },
        { Pages::Run, "Run" },
        { Pages::Abort, "Abort" },
        { Pages::Error, "Error" },
    };

    auto it = pagesMap.find(s);
    return (it != pagesMap.end()) ? it->second : "[Unknown Page_type]";
}

#endif // PAGES_ENUMERATION_H