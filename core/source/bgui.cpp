#include "bgui.hpp"
#include "os/os.hpp"
#include <utils/vec.hpp>
#include <stdexcept>
#include <iostream>

static bool init_trigger = false;

bgui::bgui(const butil::theme& gui_theme) : m_main_layout(nullptr), m_theme(gui_theme) {
}

bgui::~bgui() {
}

void bgui::set_up() {
    init_trigger = true;
    if(!instance().m_main_layout)
        instance().set_layout<blay::layout>();
    instance().apply_theme(instance().m_theme);
}

void bgui::add_call(const std::function<void()> &f) {
    if(!init_trigger) throw std::runtime_error("BGUI::You must initialize the library.");
    m_calls.push(f);
}

blay::layout *bgui::get_layout() {
    if(!init_trigger) throw std::runtime_error("BGUI::You must initialize the library.");
    return m_main_layout.get();
}

void bgui::apply_theme(const butil::theme &gui_theme)
{
    if(!init_trigger) throw std::runtime_error("BGUI::You must initialize the library.");
    // set the theme and update clear color accordingly
    m_theme = gui_theme;
    m_main_layout->apply_theme(gui_theme);
}

butil::theme bgui::get_theme() const {
    if(!init_trigger) throw std::runtime_error("BGUI::You must initialize the library.");
    return m_theme;
}
butil::draw_data* bgui::get_draw_data() {
    if(!init_trigger) throw std::runtime_error("BGUI::You must initialize the library.");
    return &instance().m_draw_data;
}
bool bgui::shutdown_lib() {
    return true;
}
// Updates the main layout
void bgui::update() {
    if(!init_trigger) throw std::runtime_error("BGUI::You must initialize the library.");
    // the main layout must to be resized based on the window size.

    butil::vec2i w_size = bos::get_window_size();
    instance().m_main_layout->set_rect(0.f, 0.f, static_cast<float>(w_size[0]), static_cast<float>(w_size[1]));
    instance().update(*instance().m_main_layout);

    // Clean draw data and get new requests
    while(!get_draw_data()->m_quad_requests.empty()) get_draw_data()->m_quad_requests.pop();
    instance().m_main_layout->get_requests(*get_draw_data());
}
bool bgui::update_inputs(blay::layout &lay){
    auto m = bos::get_mouse_position();
    float mx = m[0];
    float my = m[1];

    bool mouse_now = bos::get_pressed(bos::input_key::mouse_left);
    bool mouse_click = (mouse_now && !m_last_mouse_left);
    bool mouse_released = (!mouse_now && m_last_mouse_left);
    
    const auto& elements = lay.get_elements();   
    const auto& modals = lay.get_modals();   

    for (size_t i = elements.size(); i-- > 0; ) {
        auto elem = elements[i].get();

        if (auto* cast = elem->as_layout())
            if(update_inputs(*cast)) {
                return true;
            }
        
        float x = elem->get_x() + lay.get_x();
        float y = elem->get_y() + lay.get_y();
        float w = elem->get_width();
        float h = elem->get_height();

        bool inside =
            mx >= x &&
            mx <= x + w &&
            my >= y &&
            my <= y + h;

        if (modals.empty()) {
            if (inside) {
                elem->on_mouse_hover();
                if (mouse_click) {
                    elem->on_clicked();
                    return true; 
                }
                if (mouse_released) {
                    elem->on_released();
                    return true; 
                }
            }
        }
        else {
            update_inputs(*modals.front());
            return true;
        }
    }
    return false;
}
void bgui::update(blay::layout &lay) {
    if(!init_trigger) throw std::runtime_error("BGUI::You must initialize the library.");
    // call pre-update functions
    while (!m_calls.empty()) {
        m_calls.front()();
        m_calls.pop();
    }
    
    lay.update();
    update_inputs(lay);
    m_last_mouse_left = bos::get_pressed(bos::input_key::mouse_left);
}