#include "elem/linear_layout.hpp"
#include "bgui.hpp"
    
linear_layout::linear_layout(const orientation& ori) {
    m_orientation = ori;
}

void linear_layout::update() {
    int cursor_x = get_x();
    int cursor_y = get_y();

    const bool vertical = (m_orientation == orientation::vertical);

    // Initialize cursor based on main alignment
    if (vertical) {
        if (m_alignment == alignment::end)
            cursor_y += get_height();
        else if (m_alignment == alignment::center)
            cursor_y += get_height() / 2;
    } else {
        if (m_alignment == alignment::end)
            cursor_x += get_width();
        else if (m_alignment == alignment::center)
            cursor_x += get_width() / 2;
    }

    // Initialize cross alignment
    if (vertical) {
        if (m_cross_alignment == alignment::center)
            cursor_x += get_width() / 2;
        else if (m_cross_alignment == alignment::end)
            cursor_x += get_width();
    } else {
        if (m_cross_alignment == alignment::center)
            cursor_y += get_height() / 2;
        else if (m_cross_alignment == alignment::end)
            cursor_y += get_height();
    }

    for (auto& elem : m_elements) {
        elem->update();

        int ex = cursor_x;
        int ey = cursor_y;

        if (vertical) {
            // Align horizontally (cross axis)
            if (m_cross_alignment == alignment::center)
                ex = get_x() + (get_width() - elem->get_width()) / 2;
            else if (m_cross_alignment == alignment::end)
                ex = get_x() + get_width() - elem->get_width();

            // Align vertically (main axis)
            if (m_alignment == alignment::start) {
                elem->set_y(ey);
                cursor_y += elem->get_height() + m_spacing[1];
            } else if (m_alignment == alignment::center) {
                elem->set_y(get_y() + (get_height() - elem->get_height()) / 2);
            } else if (m_alignment == alignment::end) {
                cursor_y -= elem->get_height() + m_spacing[1];
                elem->set_y(cursor_y);
            }
        } else {
            // Horizontal layout (mirror logic)
            if (m_cross_alignment == alignment::center)
                ey = get_y() + (get_height() - elem->get_height()) / 2;
            else if (m_cross_alignment == alignment::end)
                ey = get_y() + get_height() - elem->get_height();

            if (m_alignment == alignment::start) {
                elem->set_x(ex);
                cursor_x += elem->get_width() + m_spacing[0];
            } else if (m_alignment == alignment::center) {
                elem->set_x(get_x() + (get_width() - elem->get_width()) / 2);
            } else if (m_alignment == alignment::end) {
                cursor_x -= elem->get_width() + m_spacing[0];
                elem->set_x(cursor_x);
            }
        }

        elem->set_x(ex);
        elem->set_y(ey);
    }
}


void linear_layout::get_draw_calls(std::vector<draw_call>& calls) {
    element::get_draw_calls(calls);
    // linear layouts get the draw call in addition order
    for (auto& elem : m_elements) {
        elem->get_draw_calls(calls);
    }
};