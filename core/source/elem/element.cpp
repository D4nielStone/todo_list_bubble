#include "elem/element.hpp"
#include <cstdlib>
#include <iostream>
#include "bgui.hpp"

using namespace bgui;
void element::mark_style_dirty() {
    m_style_dirty = true;

    if (auto* lay = as_layout()) {
        lay->mark_children_style_dirty();
    }
}

void element::add_class(const std::string& cls) {
    if (std::find(classes.begin(), classes.end(), cls) != classes.end())
        return;

    classes.push_back(cls);
    mark_style_dirty();
}

void element::remove_class(const std::string& cls) {
    auto it = std::remove(classes.begin(), classes.end(), cls);
    if (it != classes.end()) {
        classes.erase(it, classes.end());
        mark_style_dirty();
    }
}

bool element::has_class(const std::string& cls) const {
    return std::find(classes.begin(), classes.end(), cls) != classes.end();
}

void element::clear_classes() {
    if (!classes.empty()) {
        classes.clear();
        mark_style_dirty();
    }
}

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

    if (!computed_style.visual.visible) return;
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

void element::process_required_size(const bgui::vec2i& available) {
    // Step 1: resolve required size
    // padding removes available intern space
    auto resolve = [&](int vertical, float max) {
        int nvertical = vertical ? 0 : 1;
        switch(computed_style.layout.size_mode[vertical]) {
            case bgui::mode::pixel:   return computed_style.layout.size[vertical];
            case bgui::mode::percent: return max * (std::clamp(computed_style.layout.size[vertical], 0.f, 100.f)/100.f);
            case bgui::mode::match_parent: return max;
            case bgui::mode::wrap_content: return vertical ? content_height() : content_width();
            case bgui::mode::stretch: return max;
        }
        return 0.f;
    };

    float w = resolve(0, available[0]);
    float h = resolve(1, available[1]);

    if(computed_style.layout.size_mode[0] == bgui::mode::same)
        w = h;
    if(computed_style.layout.size_mode[1] == bgui::mode::same)
        h = w;

    // Step 2: enforce min/max rules
    w = std::clamp((int)w, computed_style.layout.limit_min[0], computed_style.layout.limit_max[0]);
    h = std::clamp((int)h, computed_style.layout.limit_min[1], computed_style.layout.limit_max[1]);

    m_rect = { m_rect[0], m_rect[1], static_cast<int>(w), static_cast<int>(h) };
}