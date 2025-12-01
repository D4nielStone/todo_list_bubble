#pragma once
#include <unordered_map>
#include "texture.hpp"
#include "propertie.hpp"
#include <string>

namespace bgui {
    class material {
    public:
        std::string m_shader_tag{"ui::default"};
        std::unordered_map<std::string, bgui::propertie> m_properties;
        bgui::texture m_texture;
        bool m_use_tex;

        material();
        ~material();
        void set(const std::string& name, const bgui::propertie u);

        bool operator==(const material &other) const {
                return (m_texture == other.m_texture && m_shader_tag == other.m_shader_tag);
        };
    };
}