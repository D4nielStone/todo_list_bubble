#include "elem/checkbox.hpp"

void bgui::checkbox::apply_theme(const bgui::theme & t) {
    element::apply_theme(t);
    m_material.set("bg_color", color{0, 0, 0, 0});
}