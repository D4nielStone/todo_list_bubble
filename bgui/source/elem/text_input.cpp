#include "elem/text_input.hpp"
#include "bgui.hpp"

elements::text_input::text_input(const std::string& buffer, const float scale, const std::string& placeholder) :
    m_buffer(buffer, scale), m_placeholder(placeholder) {
    apply_theme(bgui::instance().get_theme());
    m_visible = false;
    m_material.m_shader.compile("quad.vs", "quad.fs");
}

elements::text_input::~text_input()
{
}

void elements::text_input::on_clicked()
{
}

void elements::text_input::on_released() {
}

void elements::text_input::on_mouse_hover() {
}

void elements::text_input::update() {
    
}

void elements::text_input::get_draw_requests(std::vector<butil::draw_request>& calls) {
    element::get_draw_requests(calls);
    m_buffer.get_draw_requests(calls);
}
void elements::text_input::apply_theme(const butil::theme& t) {
    m_buffer.apply_theme(t);
}