
#include "lay/linear.hpp"
#include "bgui.hpp"
#include <iostream>
using namespace bgui;
    
linear::linear(const orientation& ori) : m_orientation(ori) {
    m_visible = false;
}

void linear::update() {
    if (m_elements.empty()) return;

    // updates the logic and size of child elements
    for(auto& elem : m_elements) {
        elem->update();
        elem->update_size(get_final_size() - vec2i{
            get_padding()[0] + get_padding()[2],
            get_padding()[1] + get_padding()[3]
            }*2);
    }

    const bool vertical = (m_orientation == orientation::vertical);
    const int main_index = vertical ? 1 : 0;
    const int cross_index = vertical ? 0 : 1;

    // padding on main axis (start and end)
    int pad_main_start = (vertical ? m_padding[1] : m_padding[0]);
    int pad_main_end = (vertical ? m_padding[3] : m_padding[2]);
    // Available size on main axis (respect padding)
    const int available_main = get_final_size()[main_index] - (pad_main_start + pad_main_end);

    int elem_total_main = 0;

    // Sum child sizes + spacing
    for (auto& elem : m_elements) {
        elem_total_main += elem->get_final_size()[main_index] + elem->get_margin()[main_index] + elem->get_margin()[main_index+2];
    }

    // Starting cursor depending on alignment
    int cursor_main = 0;

    switch (m_alignment) {
        case alignment::start:
            cursor_main = pad_main_start + m_elements.begin()->get()->get_margin()[main_index];
            break;

        case alignment::center:
            cursor_main = (available_main - elem_total_main) / 2;
            break;

        case alignment::end:
            cursor_main = pad_main_start + available_main - elem_total_main - m_elements.begin()->get()->get_margin()[main_index+2];
            break;
        default:
            break;
    }

    // Place elem
    for (auto& elem : m_elements) {

        int cross_pos = 0;

        const int cross_size = elem->get_final_size()[cross_index];
        const int container_cross = get_final_size()[cross_index];

        int pad_cross_start = (!vertical ? m_padding[1] : m_padding[0]);
        int pad_cross_end = (!vertical ? m_padding[3] : m_padding[2]);

        // Cross-axis alignment
        switch (m_cross_alignment) {
            case alignment::start:
                cross_pos = pad_cross_start;
                break;

            case alignment::center:
                cross_pos = (container_cross - cross_size) / 2;
                break;

            case alignment::end:
                cross_pos = container_cross - cross_size - pad_cross_end;
                break;
        }

        // Set position
        if (vertical) {
            elem->set_final_rect(cross_pos + get_final_x(), cursor_main + get_final_y(), elem->get_final_width(), elem->get_final_height());
        } else {
            elem->set_final_rect(cursor_main + get_final_x(), cross_pos + get_final_y(), elem->get_final_width(), elem->get_final_height());
        }

        // Advance in main axis (add child margin on the main axis if any)
        cursor_main += elem->get_final_size()[main_index] + elem->get_margin()[main_index+2];
    }
}