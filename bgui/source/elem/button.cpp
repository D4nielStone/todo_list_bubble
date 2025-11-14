#include "elem/button.hpp"
#include "bgui.hpp"

elements::button::button(const std::string &name, const float scale, const std::function<void()> &f) : 
    m_label(name, scale), m_function(f) {
    set_theme(bgui::instance().get_theme());
    bgui::instance().add_gl_call([&](){
        m_material.m_shader.compile("quad.vs", "quad.fs");
    });
}

elements::button::~button() {
}

void elements::button::update() {
    set_size(m_label.get_width() + m_intern_spacing[0]*2, m_label.get_height() + m_intern_spacing[1]*2);
}

void elements::button::get_draw_calls(std::vector<draw_call> &calls) {
    element::get_draw_calls(calls);
    m_label.set_position(get_x() + m_intern_spacing[0], get_y() + m_intern_spacing[1]);
    m_label.get_draw_calls(calls);
}

void elements::button::set_theme(const butil::theme &t) {
    m_material.set("u_bg_color", t.m_button_color);
    m_material.set("u_bordered", true);
    m_material.set("u_border_radius", 5.f);
    m_material.set("u_border_size", 5.f);
    m_material.set("u_border_color", t.m_button_border_color);
    m_material.m_visible = true;
}