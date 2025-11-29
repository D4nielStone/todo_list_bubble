#include <bgui_backend_freetype.hpp>
#include <stdexcept>
#include <iostream>
#include <filesystem>

static std::unordered_map<std::string, std::string> s_system_fonts;
static FT_Library s_ft;
void bkend::set_up_freetype() {
    if (FT_Init_FreeType(&s_ft)) {
        throw std::runtime_error("Error initializing Freetype.");
    }
    ft_search_system_fonts();
    ft_load_font("Noto Sans-Condensed", s_system_fonts["Noto Sans-Condensed"], bos::font_manager::m_default_resolution);
}
void bkend::shutdown_freetype() {
    FT_Done_FreeType(s_ft);
}

// Searches common system font directories and populates s_system_fonts.
// Note: this implementation just store the font paths; loading fonts is handled elsewhere.
void bkend::ft_search_system_fonts() {
    #ifdef _WIN32
        std::string folder = "C:\\Windows\\Fonts";
    #else
        std::string folder = "/usr/share/fonts";
    #endif

    for (const auto &entry : std::filesystem::recursive_directory_iterator(folder)) {
        if (entry.is_regular_file()) {
            auto path = entry.path().string();
            if (!(path.ends_with(".ttf") || path.ends_with(".otf")))
                continue;
            FT_Face face;
            if (!FT_New_Face(s_ft, path.c_str(), 0, &face)) {
                std::string family_name  = face->family_name ? face->family_name : "(unknown)";
                std::string style = face->style_name ? face->style_name : "(unknown)";
                s_system_fonts[family_name + "-" + style] = path;
                FT_Done_Face(face);
            }
        }
    }
}

bos::font &bkend::ft_load_font(const std::string &font_name, const std::string &font_path, unsigned int resolution) {
    // Font from cache
    if (bos::font_manager::instance().has_font(font_name) && 
    bos::font_manager::instance().get_font(font_name).atlas.m_path == font_path)
        return bos::font_manager::instance().get_font(font_name);

    FT_Face face{};
    if (FT_New_Face(s_ft, font_path.c_str(), 0, &face))
        throw std::runtime_error("Error loading font: " + font_name + ". Wrong name?");
    
    FT_Set_Pixel_Sizes(face, 0u, resolution);
    
    bos::font _font{};
    _font.atlas.m_path = font_path;
    
    int padding = 2;
    int width = 0;
    int max_height = 0;
    int ascent=0, descent=0;

    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1); TODO: move to opengl backend
    
    // First pass: compute total atlas size
    for (unsigned int c = 32; c < 256; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "Missing glyph: " << c << "\n";
            continue;
        }

        ascent = std::max(ascent, face->glyph->bitmap_top);
        int desc = face->glyph->bitmap.rows - face->glyph->bitmap_top;
        descent = std::max(descent, desc);
        width += face->glyph->bitmap.width + padding;
        max_height = ascent + descent;
    }
    /*
    
    // Create atlas texture
    unsigned int atlasTex = 0;
    glGenTextures(1, &atlasTex);
    glBindTexture(GL_TEXTURE_2D, atlasTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, max_height, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    */ //TODO: move to opengl backend
    
    // Fill atlas
    int xOffset = 0;
    for (unsigned int c = 32; c < 256; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "Missing glyph: " << c << "\n";
            continue;
        }
        FT_Bitmap& bmp = face->glyph->bitmap;
    
        int yOffset = ascent - face->glyph->bitmap_top;
        //glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset, bmp.width, bmp.rows, GL_RED, GL_UNSIGNED_BYTE, bmp.buffer);
        // Fill atlas buffer
        _font.atlas.m_buffer.resize(width * max_height);
        for(int row = 0; row < bmp.rows; row++) {
            for(int col = 0; col < bmp.width; col++) {
                int atlas_index = (yOffset + row) * width + (xOffset + col);
                int bmp_index = row * bmp.width + col;
                _font.atlas.m_buffer[atlas_index] = bmp.buffer[bmp_index];
            }
        }
        _font.atlas.m_size = { (float)bmp.width, (float)bmp.rows };
        _font.atlas.m_offset = { (float)xOffset, (float)yOffset };

        // Compute normalized UVs
        float u0 = xOffset / (float)width;      // left
        float u1 = (xOffset + bmp.width) / (float)width;    // right
        float v0 = (float)yOffset / (float)max_height;                  // topo normalizado
        float v1 = (float)(yOffset + bmp.rows) / (float)max_height;     // fundo normalizado

    
        // Store glyph
        bos::character ch{};
        ch.size = { bmp.width, bmp.rows };
        ch.bearing = { face->glyph->bitmap_left, face->glyph->bitmap_top };
        ch.advance = face->glyph->advance.x >> 6;
        ch.uv_min = { u0, v0 };
        ch.uv_max = { u1, v1 };
    
        _font.chs.emplace(c, ch);
        xOffset += bmp.width + padding;
    }
    
    _font.atlas_size = { (float)width, (float)max_height };
    _font.ascent   = face->size->metrics.ascender / 64.0f;
    _font.descent  = std::abs(face->size->metrics.descender / 64.0f);
    _font.line_gap = (face->size->metrics.height / 64.0f) - (_font.ascent + _font.descent);

    bos::font_manager::instance().m_fonts.emplace(font_name, _font);
    FT_Done_Face(face);
    return bos::font_manager::instance().m_fonts[font_name];
}