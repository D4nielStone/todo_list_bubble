#pragma once
#include <string>
#include <utility>
#include <unordered_map>
#include "utils/vec.hpp"
#include "utils/draw.hpp"

namespace bos {
    // \brief Represents a single character glyph in a font.
    struct character {
        butil::vec<2, unsigned int> size{0, 0};
        butil::vec<2, int> bearing{0, 0};
        long int advance{0};
        butil::vec2 uv_min{0.f};
        butil::vec2 uv_max{0.f};
    };

    // \brief Represents a font with its character glyphs and texture atlas.
    struct font {      
        butil::texture atlas;
        std::unordered_map<char32_t, bos::character> chs{};
        butil::vec2 atlas_size{0.f, 0.f};
        unsigned int resolution = 0;
        float ascent = 0.0f;
        float descent = 0.0f;
        float line_gap = 0.0f;
    };

    struct font_manager {
        std::unordered_map<std::string, font> m_fonts;
        static constexpr float m_default_resolution = 40.f;
        static font_manager& instance() {
            static font_manager f;
            return f;
        }
        font_manager();
        ~font_manager();
        font& get_font(const std::string& name);
        bool has_font(const std::string& name);
    };
} // namespace bos