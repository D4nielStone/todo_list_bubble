#include "elem/linear_layout.hpp"
#include "bgui.hpp"
    
linear_layout::linear_layout(const orientation& ori) {
    m_orientation = ori;
    m_material.m_visible = false;
    m_material.m_shader.compile("quad.vs", "quad.fs");
}

void linear_layout::update() {
    // no children -> nothing to do
    if (m_elements.empty()) return;

    layout::update();
    const bool vertical = (m_orientation == orientation::vertical);

    // compute total main-axis size (sum of widths or heights) + spacing between items
    int spacing = vertical ? m_spacing_elements[1] : m_spacing_elements[0];
    int total_main = 0;
    for (auto& elem : m_elements) {
    if (vertical)
        total_main += elem->get_height() + elem->m_extern_spacing[1];
    else
        total_main += elem->get_width() + elem->m_extern_spacing[0];
    }

    if (m_elements.size() > 1) total_main += spacing * (int(m_elements.size()) - 1);

    // compute starting cursor on the main axis depending on alignment (start/center/end)
    int cursor_main;
    if (vertical) {
        if (m_alignment == alignment::start)
            cursor_main = m_padding[1];
        else if (m_alignment == alignment::center)
            cursor_main = (get_height() - total_main) / 2;
        else // end
            cursor_main = get_height() - total_main;
    } else {
        if (m_alignment == alignment::start)
            cursor_main = m_padding[0];
        else if (m_alignment == alignment::center)
            cursor_main = (get_width() - total_main) / 2;
        else // end
            cursor_main = get_width() - total_main;
    }

    // Place each child using cursor_main and cross-axis alignment
    for (auto& elem : m_elements) {
        // child already updated above
        int ex = 0;
        int ey = 0;

        if (vertical) {
            // cross-axis (horizontal) alignment for this child
            if (m_cross_alignment == alignment::start)
                ex = m_padding[1];
            else if (m_cross_alignment == alignment::center)
                ex = (get_width() - elem->get_width()) / 2;
            else // end
                ex = get_width() - elem->get_width();

            // main-axis position = cursor_main (y)
            ey = cursor_main;

            // commit positions
            elem->set_x(ex);
            elem->set_y(ey);

            // advance cursor
            cursor_main += elem->get_height() + spacing + elem->m_extern_spacing[1];
        } else {
            // cross-axis (vertical) alignment for this child
            if (m_cross_alignment == alignment::start)
                ey = m_padding[0];
            else if (m_cross_alignment == alignment::center)
                ey = (get_height() - elem->get_height()) / 2;
            else // end
                ey = get_height() - elem->get_height();

            // main-axis position = cursor_main (x)
            ex = cursor_main;

            // commit positions
            elem->set_x(ex);
            elem->set_y(ey);

            // advance cursor
            cursor_main += elem->get_width() + spacing + elem->m_extern_spacing[0];
        }
    }
}
void linear_layout::fit_to_content() {
    const bool vertical = (m_orientation == orientation::vertical);
    int max_cross = 0;
    for (auto& elem : m_elements) {
        int cross = vertical ? elem->get_width() : elem->get_height();
        if (cross > max_cross)
            max_cross = cross;
    }

    if (vertical) {
        set_width(max_cross + m_padding[0]*2);
    } else {
        set_height(max_cross + m_padding[1]*2);
    }
}