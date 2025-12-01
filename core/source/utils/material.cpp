#include "utils/material.hpp"
#include "bgui.hpp"

bgui::material::material() : m_use_tex(false) {
}
bgui::material::~material() {
}
/*
void bgui::material::bind_properties() {
    m_shader.bind();

    for(const auto& [name, u] : m_properties) {
        m_shader.set(name, u);
    }

    if(m_use_tex) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        m_shader.set("texture", 0);
    }
}*/
void bgui::material::set(const std::string &name, const bgui::propertie u) {
    m_properties[name] = u;
}