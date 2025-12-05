#include "elem/button.hpp"
#include "bgui.hpp"
#include <iostream>

bgui::button::button(const std::string &name, const float scale, const std::function<void()> &f) : 
    m_label(name, scale), m_function(f), m_label_alignment(bgui::alignment::center) {
        set_padding(5, 2);
        set_width(mode::wrap_content);
        set_height(mode::wrap_content);
}

bgui::button::~button() {
}

void bgui::button::update() {
    m_material.set("bg_color", m_theme.m_button_color);
}

void bgui::button::get_requests(bgui::draw_data* data) {
    // TODO: optimize: avoid re-updateing label position if not changed
    element::get_requests(data);
    switch(m_label_alignment) {
        case bgui::alignment::start:
            m_label.set_final_rect(get_final_x() + m_padding[0], get_final_y() + m_padding[1], m_label.get_final_width(), m_label.get_final_height());
            break;
        case bgui::alignment::center:
            m_label.set_final_rect(
                get_final_x() + (get_final_width() - m_label.get_final_width()) / 2,
                get_final_y() + (get_final_height() - m_label.get_final_height()) / 2,
                m_label.get_final_width(),
                m_label.get_final_height()
            );
            break;
        case bgui::alignment::end:
            m_label.set_final_rect(
                get_final_x() + get_final_width() - m_label.get_final_width() - m_padding[0],
                get_final_y() + get_final_height() - m_label.get_final_height() - m_padding[1],
                m_label.get_final_width(),
                m_label.get_final_height()
            );
            break;
        default:
            break;
    }
    m_label.get_requests(data);
}


float bgui::button::content_height() {
    return m_label.get_final_height();
}

float bgui::button::content_width() {
    return m_label.get_final_width();
}

void bgui::button::apply_theme(const bgui::theme &t) {
    element::apply_theme(t);
    m_visible = true;
    m_label.apply_theme(t);
}

void bgui::button::on_released() {
}
void bgui::button::on_clicked() {
    m_material.set("bg_color", bgui::get_theme().m_button_clicked_color);
    bgui::add_function(m_function);
}
void bgui::button::on_mouse_hover() {
    m_material.set("bg_color", bgui::get_theme().m_button_hovered_color);
}