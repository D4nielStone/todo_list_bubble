#include "os/font.hpp"
#include <stdexcept>
#include <filesystem>
#include <iostream>

bos::font_manager::font_manager() {
    if (FT_Init_FreeType(&ft)) {
        throw std::runtime_error("Error initializing Freetype.");
    }
}

bos::font_manager::~font_manager() {
    m_fonts.clear();
    FT_Done_FreeType(ft);
}

bos::font &bos::font_manager::load_font(const std::string &font_name, const std::string &font_path, FT_UInt resolution) {
    if (has_font(font_name)) return m_fonts[font_name];

    FT_Face face{};

    /*if (m_fonts_memoria.find(std::filesystem::path(nome_da_fonte).filename().string()) != m_fonts_memoria.end())
    {
        if (FT_New_Memory_Face(ft, m_fonts_memoria.at((std::filesystem::path(nome_da_fonte).filename().string())).first, m_fonts_memoria.at((std::filesystem::path(nome_da_fonte).filename().string())).second, 0, &face))
        {
            throw std::runtime_error("Erro ao carregar a fonte: " + nome_da_fonte);
        }
    }
    else*/
        
    if (std::filesystem::exists(font_path)) {
        if (FT_New_Face(ft, font_path.c_str(), m_fonts.size(), &face)) {
            throw std::runtime_error("Error loading the font " + font_name + " with path:" + font_path);
        }
    }

    FT_Set_Pixel_Sizes(face, 0u, resolution);

    font _font;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for (unsigned int c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "Error loading character: " << c;
            continue;
        }

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        character _character = {
            texture,
            butil::vec<2, unsigned int>{face->glyph->bitmap.width, face->glyph->bitmap.rows},
            butil::vec<2, FT_Int>{face->glyph->bitmap_left, face->glyph->bitmap_top},
            face->glyph->advance.x
        };
        _font.emplace(c, _character);
    }

    m_fonts.emplace(font_name, _font);

    FT_Done_Face(face);
}

bool bos::font_manager::has_font(const std::string &name) {
    return m_fonts.find(name) != m_fonts.end();
}
bos::font &bos::font_manager::get_font(const std::string& name) {
    if (has_font(name)) return m_fonts[name];
    else throw std::runtime_error("trying to get an invalid font.");
}