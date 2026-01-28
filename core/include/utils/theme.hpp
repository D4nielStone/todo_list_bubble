#pragma once
#include <unordered_map>
#include "style.hpp"

namespace bgui {

    struct theme {
        style base;
        std::unordered_map<std::string, style> types;
        std::unordered_map<std::string, style> classes;
    };

    // Dark theme based on old dark_style color scheme
    bgui::theme dark_theme();
}