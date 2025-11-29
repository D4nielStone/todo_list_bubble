#include "os/font.hpp"
#include <stdexcept>
#include <filesystem>
#include <iostream>

bos::font_manager::font_manager() {
    m_fonts.clear();
}

bos::font_manager::~font_manager() {
    m_fonts.clear();
}

bool bos::font_manager::has_font(const std::string &name) {
    return m_fonts.find(name) != m_fonts.end();
}
bos::font &bos::font_manager::get_font(const std::string& name) {
    if(has_font(name))
        return m_fonts[name];
    else throw std::runtime_error("Font " + name + " not found. Have you added it to the backend?");
}
