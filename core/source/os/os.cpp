#include <fstream>
#include <sstream>
#include <iostream>
#include "os/os.hpp"

static bos::windowio s_window_io;

bos::windowio &bos::get_window() {
    return s_window_io;
}
butil::vec2i bos::get_window_size() {
    return get_window().m_size;
}
butil::vec2i bos::get_mouse_position() {
    return bos::get_window().m_mouse_position;
}
std::string bos::read_file(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + path + "\n");
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

butil::mat4 bos::get_projection() {
    auto size = bos::get_window_size();
    auto width = size[0];
    auto height = size[1];
    return butil::orthographic(0.0f, static_cast<float>(width), static_cast<float>(height), 0.f);
}

bool bos::get_pressed(const bos::input_key& k) {
    if(bos::get_window().m_input_map[k] == bos::input_action::press) return true;
    return false;
}