#pragma once
#include <unordered_map>
#include "style.hpp"

namespace bgui {

    struct theme {
        style base;
        std::unordered_map<std::string, style> types;
        std::unordered_map<std::string, style> classes;
    };

    // Default themes:
    inline bgui::theme dark_theme() {
        bgui::theme t;

        // ---------- DEFAULT ----------
        t.base.visual.background.normal = {0.15f,0.15f,0.15f,1.f};
        t.base.visual.text.normal       = {1.f,1.f,1.f,1.f};

        // ---------- PANEL ----------
        t.types["linear"].layout.padding = {10,10,10,10};
        t.types["linear"].visual.visible = true;

        // ---------- BUTTON ----------
        t.types["button"].visual.background.normal = {0.2f,0.4f,0.8f,1.f};
        t.types["button"].visual.background.hover  = {0.3f,0.5f,0.9f,1.f};
        t.types["button"].visual.border_radius     = 6.f;

        // ---------- PRIMARY ----------
        t.classes["primary"].visual.background.normal = {0.8f,0.2f,0.2f,1.f};

        return t;
}
}