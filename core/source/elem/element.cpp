#include "elem/element.hpp"
#include <cstdlib>
#include <iostream>
#include "bgui.hpp"

using namespace bgui;

void element::set_enable(bool b){
    m_enabled = b;
}

void element::on_update() {
    m_last_drag = {0, 0};
}

vec2i bgui::element::is_drag() const {
    return m_last_drag;
}
void element::get_requires(bgui::draw_data* calls) {

    //if (!m_visible) return;
    calls->m_quad_requires.push({
        m_material,
        6,
        vec4{
            static_cast<float>(m_rect[0]),
            static_cast<float>(m_rect[1]),
            static_cast<float>(m_rect[2]),
            static_cast<float>(m_rect[3])
        }
    });
}
void bgui::element::apply_style(const style & style) {
    /*m_style = style;
    m_material.set("bg_color", m_style.m_box_color);
    m_material.set("bordered", (bool)m_style.m_box_color[3]);
    m_material.set("border_radius", 2.f);
    m_material.set("border_size", 1.f);
    m_material.set("border_color", m_style.m_button_border_color);*/
}

void element::process_required_size(const bgui::vec2i& available) {
    // Step 1: resolve required size
    // padding removes available intern space
    /*auto resolve = [&](int vertical, float max) {
        int nvertical = vertical ? 0 : 1;
        switch(m_required_mode[vertical]) {
            case bgui::mode::pixel:   return m_required_size[vertical];
            case bgui::mode::percent: return max * (std::clamp(m_required_size[vertical], 0.f, 100.f)/100.f);
            case bgui::mode::match_parent: return max;
            case bgui::mode::wrap_content: return vertical ? content_height() : content_width();
            case bgui::mode::stretch: return max;
        }
        return 0.f;
    };

    float w = resolve(0, available[0]);
    float h = resolve(1, available[1]);

    if(m_required_mode[0] == bgui::mode::same)
        w = h;
    if(m_required_mode[1] == bgui::mode::same)
        h = w;

    // Step 2: enforce min/max rules
    w = std::clamp((int)w, m_min_size[0], m_max_size[0]);
    h = std::clamp((int)h, m_min_size[1], m_max_size[1]);

    m_rect = { m_rect[0], m_rect[1], static_cast<int>(w), static_cast<int>(h) };*/
}