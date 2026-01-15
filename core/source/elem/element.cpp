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
void bgui::element::apply_style(const bgui::style& resolved_style, input_state state) {
    const auto& visual = resolved_style.visual;

    // Background
    color bg = visual.background.resolve(
        state,
        {0, 0, 0, 0}
    );
    m_material.set("bg_color", bg);

    // Border
    color border = visual.border.resolve(
        state,
        {0, 0, 0, 0}
    );
    m_material.set("border_color", border);

    bool has_border = border[3] > 0.0f;
    m_material.set("bordered", has_border);

    m_material.set(
        "border_radius",
        visual.border_radius
    );

    // Text (if needed)
    if ((*visual.text.normal)[3] != 0) {
        color text = visual.text.resolve(
            state,
            {1, 1, 1, 1}
        );
        m_material.set("text_color", text);
    }
}

void element::process_required_size(const bgui::vec2i& available) {
    // Step 1: resolve required size
    // padding removes available intern space
    auto resolve = [&](int vertical, float max) {
        int nvertical = vertical ? 0 : 1;
        switch((*style.layout.size_mode)[vertical]) {
            case bgui::mode::pixel:   return (*style.layout.size)[vertical];
            case bgui::mode::percent: return max * (std::clamp((*style.layout.size)[vertical], 0.f, 100.f)/100.f);
            case bgui::mode::match_parent: return max;
            case bgui::mode::wrap_content: return vertical ? content_height() : content_width();
            case bgui::mode::stretch: return max;
        }
        return 0.f;
    };

    float w = resolve(0, available[0]);
    float h = resolve(1, available[1]);

    if((*style.layout.size_mode)[0] == bgui::mode::same)
        w = h;
    if((*style.layout.size_mode)[1] == bgui::mode::same)
        h = w;

    // Step 2: enforce min/max rules
    w = std::clamp((int)w, (*style.layout.limit_min)[0], (*style.layout.limit_max)[0]);
    h = std::clamp((int)h, (*style.layout.limit_min)[1], (*style.layout.limit_max)[1]);

    m_rect = { m_rect[0], m_rect[1], static_cast<int>(w), static_cast<int>(h) };
}