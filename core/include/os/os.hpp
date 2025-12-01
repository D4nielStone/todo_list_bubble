#pragma once
#include <unordered_map>
#include <string>
#include "utils/vec.hpp"
#include "utils/mat.hpp"

namespace bos {
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
        butil::vec2i m_size{800, 600};
        butil::vec2i m_mouse_position{0, 0};
        std::unordered_map<input_key, input_action> m_input_map;
        std::string m_title{""};
    };
    windowio& get_window();
    butil::vec2i get_window_size();
    butil::vec2i get_mouse_position();
    std::string read_file(const std::string& path);
    butil::mat4 get_projection();
    bool get_pressed(const input_key&);
} // namespace bos