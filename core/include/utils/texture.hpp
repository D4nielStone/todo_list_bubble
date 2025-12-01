#pragma once
#include <string>
#include <vector>
#include "vec.hpp"

namespace bgui {
    struct texture {
        std::string m_path{"default"};
        bool m_has_alpha = false;
        bool m_use_red_channel = false;
        bool m_generate_mipmap = true;
        std::vector<unsigned char> m_buffer;
        bgui::vec2 m_offset = {0,0};
        bgui::vec2 m_size = {0,0};

        bool operator==(const texture& other) const {
            return (m_buffer == other.m_buffer);
        }
    };
} // namespace bgui