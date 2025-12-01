#include "elem/text_input.hpp"
#include "bgui.hpp"

bgui::text_input::text_input(const std::string& buffer, const float scale, const std::string& placeholder) :
    m_buffer(buffer, scale), m_placeholder(placeholder) {
    apply_theme(bgui::get_theme());
    m_visible = false;
    m_material.m_shader_tag = "ui::default";
}

bgui::text_input::~text_input()
{
}

void bgui::text_input::on_clicked()
{
}

void bgui::text_input::on_released() {
}

void bgui::text_input::on_mouse_hover() {
}

void bgui::text_input::update() {
    
}

void bgui::text_input::get_requests(bgui::draw_data* data) {
    element::get_requests(data);
    m_buffer.get_requests(data);
}
void bgui::text_input::apply_theme(const bgui::theme& t) {
    m_buffer.apply_theme(t);
}