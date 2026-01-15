#include "elem/checkbox.hpp"
#include "elem/button.hpp"
#include "os/os.hpp"

bgui::checkbox::checkbox(bool* ref, bool actv, const std::string& title, const float scale) : m_ref(ref), m_active(actv), linear(bgui::orientation::horizontal) {

    type = "checkbox";
    style.visual.visible = true;
    recives_input(true);
    style.layout.cross_align = (alignment::center);

    // box should be a button
    auto& box = add<bgui::element>();
    if(title.empty() == false) {
        auto& txt = add<text>(title, scale);
        label = &txt;
        txt.recives_input(false);
        txt.style.layout.require_width(mode::stretch);
        txt.style.layout.align = alignment::end;
    }
    
    box.recives_input(false);
    style.layout.require_width(mode::match_parent);
    style.layout.require_height(mode::wrap_content);
    box.style.layout.margin = {5, 5};
    box.style.layout.require_height(mode::match_parent);
    box.style.layout.require_width(mode::same);
}
bgui::checkbox::checkbox(const std::string& title, const float scale, const bool actv) : m_ref(nullptr), m_active(actv), linear(bgui::orientation::horizontal) {
    //m_visible = true;
    recives_input(true);

    // box should be a button
    auto& box = add<bgui::element>();
    if(title.empty() == false) {
        auto& txt = add<text>(title, scale);
        label = &txt;
        txt.style.layout.margin = {0, 2};
        txt.recives_input(false);
        txt.style.layout.require_width(mode::stretch);
        txt.style.layout.align = alignment::end;
    }
    
    box.recives_input(false);
    style.layout.require_width(mode::match_parent);
    style.layout.require_height(mode::wrap_content);
    box.style.layout.margin = {10, 10};
    box.style.layout.require_height(mode::match_parent);
    box.style.layout.require_width(mode::same);
}

void bgui::checkbox::on_clicked() {
    bgui::get_context().m_actual_cursor = cursor::hand;
    m_active = m_active ? false : true;
    if(m_ref != nullptr) *m_ref = m_active;
    if(m_function) m_function(m_active);
}

void bgui::checkbox::set_on_change(const std::function<void(bool)>& f) {
    m_function = f;
}

void bgui::checkbox::on_released() {
    bgui::get_context().m_actual_cursor = cursor::hand;
}
void bgui::checkbox::on_pressed() {
    bgui::get_context().m_actual_cursor = cursor::hand;
}
void bgui::checkbox::on_mouse_hover() {
    bgui::get_context().m_actual_cursor = cursor::hand;
}

void bgui::checkbox::on_update() {
    linear::on_update();
    m_active_color[3] = m_active ? 1.f : 0.f;
    auto bc = m_active_color/2;
    bc[3] = 1.f;
    get_elements()[0]->style.visual.background.normal = m_active_color;
    get_elements()[0]->style.visual.border.normal = bc;
}

bgui::text& bgui::checkbox::get_label() {
    return *label;
}