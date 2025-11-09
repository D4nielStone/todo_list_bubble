#pragma once
#include <glad/glad.h>
#include <string>
#include <utility>
#include <unordered_map>
#include "utils/vec.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

namespace bos {
    struct character {
        GLuint m_tex{0};
        butil::vec<2, unsigned int> size{0, 0};
        butil::vec<2, FT_Int> offset{0, 0};
        long int advance{0};
    };

    // font translates is a map to translate char in bos::character.
    using font = std::unordered_map<char32_t, bos::character>;

    class font_manager {
    private:
        std::unordered_map<std::string, font> m_fonts;
        FT_Library ft;
    public:
        static font_manager& instance() {
            static font_manager f;
            return f;
        }
        font_manager();
        ~font_manager();
        font& load_font(const std::string& font_name, const std::string& font_path, FT_UInt resolution);
        font& get_font(const std::string& name);
        bool has_font(const std::string& name);
    };
} // namespace bos