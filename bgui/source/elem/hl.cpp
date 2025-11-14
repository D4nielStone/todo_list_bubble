#include "elem/hl.hpp"
#include "bgui.hpp"
    
using namespace elements;

hl::hl() {
    set_size(500, 5);
    set_theme(bgui::instance().get_theme());
    bgui::instance().add_gl_call([&](){
        m_material.m_shader.compile("quad.vs", "quad.fs");
    });
}

void hl::update() {
}
void hl::set_theme(const butil::theme &t) {
    m_material.set("u_bg_color", t.m_hl_color);
    m_material.set("u_bordered", true);
    m_material.set("u_border_radius", 5.f);
    m_material.set("u_border_size", 5.f);
    m_material.set("u_border_color", t.m_hl_color);
    m_material.m_visible = true;
}