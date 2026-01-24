#include "elem/input_area.hpp"
#include "os/os.hpp"
#include "bgui.hpp"

bgui::input_area::input_area(const std::string& buffer, const float scale, const std::string& placeholder) :
    linear(), m_placeholder(placeholder) {
    type = "inputarea";
}

bgui::input_area::~input_area() {
}

void bgui::input_area::on_pressed() {
    bgui::get_context().m_actual_cursor = bgui::cursor::ibeam;
}

void bgui::input_area::on_clicked() {
    bgui::get_context().m_actual_cursor = bgui::cursor::ibeam;
}

void bgui::input_area::on_released() {
    bgui::get_context().m_actual_cursor = bgui::cursor::ibeam;
}

void bgui::input_area::on_mouse_hover() {
    bgui::get_context().m_actual_cursor = bgui::cursor::ibeam;
}

bgui::text& bgui::input_area::get_label() {
    return *m_text;
}

void bgui::input_area::on_update() {
    if(m_input_buffer.empty()) {
        m_text->set_buffer(m_placeholder);
    }
    else {
        m_text->set_buffer(m_input_buffer);
    }
    linear::on_update();
}

void bgui::input_area::get_requires(bgui::draw_data* data) {
    linear::get_requires(data);
}