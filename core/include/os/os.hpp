#pragma once
#include <unordered_map>
#include <string>
#include "utils/vec.hpp"
#include "utils/mat.hpp"

namespace bgui {
    enum class input_key {
        none,
        mouse_left,
        mouse_right,
        mouse_middle
    };
    enum class input_action {
        none,
        press,
        release,
        repeat
    };
    struct windowio {
        bgui::vec2i m_size{800, 600};
        bgui::vec2i m_mouse_position{0, 0};
        std::unordered_map<input_key, input_action> m_input_map;
        std::string m_title{""};
        bool m_last_mouse_left = false;
    };
    windowio& get_window();
    bgui::vec2i get_window_size();
    bgui::vec2i get_mouse_position();
    std::string read_file(const std::string& path);
    bgui::mat4 get_projection();
    bool get_pressed(const input_key&);
} // namespace bgui