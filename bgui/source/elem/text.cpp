#include "elem/text.hpp"
#include <bgui.hpp>
#include <iostream>
#include <codecvt>
#include <locale>

std::u32string utf8_to_utf32(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
    return conv.from_bytes(str);
}

elements::text::text(const std::string &buffer, float scale) : m_buffer(buffer),
 m_font_name("Noto Sans-Condensed"), m_scale(scale) {
    set_font(m_font_name);
    set_theme(bgui::instance().get_theme());
    bgui::instance().add_gl_call([&](){
        m_material.m_shader.compile("assets/quad.vs", "assets/text.fs");
    });
}
elements::text::~text() {
}
void elements::text::update() {
}
void elements::text::set_font(const std::string &path) {
    auto& i = bos::font_manager::instance();
    m_font = i.get_font(path);
}

void elements::text::get_draw_calls(std::vector<draw_call>& calls) {
    float line_size = m_scale * bos::font_manager::m_default_resolution;
    const auto& chs = m_font.chs;
    float line_y = line_size;
    float line_x = 0; 
    float init_x = get_x();
        
    m_material.m_texture = m_font.atlas;
        
    int total_width = 0, total_height = 0;
    for(char32_t ca : utf8_to_utf32(m_buffer)) {
        if (chs.empty()) return;
        // break line
        if(ca == '\n') {line_y += line_size; line_x = 0; continue;}

        // set char
        bos::character ch{};
        if(chs.find(ca) != chs.end()) ch = chs.at(ca);
        else continue;
        
        auto bearing = (ch.bearing);
        auto size = (ch.size);
        float xpos = get_x() + line_x + m_scale * bearing[0];
        float ypos = get_y() + line_y - (m_scale * bearing[1] - m_scale * size[1]);

        float w = m_scale * size[0];
        float h = m_scale * size[1];
    
        calls.push_back({
            m_material, bgui::instance().get_quad_vao(), GL_TRIANGLES, 6, {
                xpos, ypos, w, -h
            }, ch.uv_min, ch.uv_max
        });

        line_x += ch.advance * m_scale;
        total_height = line_y;
    }
    total_width = line_x;
    set_size(total_width, total_height);
};