#include "element.hpp"

void element::set_position(int x, int y) {
    m_x = x;
    m_y = y;
}

void element::set_size(int width, int height) {
    m_width = width;
    m_height = height;
}

void element::set_x(int x) {    
    m_x = x;
}

void element::set_y(int y) {    
    m_y = y;
}

void element::set_rect(int x, int y, int width, int height) {
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
}

int element::get_x() const {
    return m_x;
}

int element::get_y() const {
    return m_y;
}

int element::get_height() const {
    return m_height;
}

int element::get_width() const {
    return m_width;
}
