#pragma once
#include <os/font.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace bkend {
    void set_up_freetype();
    void shutdown_freetype();
    bos::font& ft_load_font(const std::string& font_name, const std::string& font_path, unsigned int resolution);
    void ft_search_system_fonts();
} // namespace bgui