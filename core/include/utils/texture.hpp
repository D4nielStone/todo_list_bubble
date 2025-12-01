#pragma once
#include <string>
#include <vector>
#include "vec.hpp"

namespace butil {
    struct texture {
        std::string m_path{"default"};
        bool m_has_alpha = false;
        bool m_use_red_channel = false;
        bool m_generate_mipmap = false;
        std::vector<unsigned char> m_buffer;
        butil::vec2 m_offset = {0,0};
        butil::vec2 m_size = {0,0};

        bool operator==(const texture& other) const {
            return (m_buffer == other.m_buffer);
        }
    };
} // namespace butil