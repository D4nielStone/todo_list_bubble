#include <glad/glad.h>
#include "bgui_backend_opengl3.hpp"
#include "opengl3_shader.hpp"
#include <bgui.hpp>
#include <os/os.hpp>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <memory>

// RAII wrapper para VAO/VBO
struct QuadVAO {
    GLuint vao = 0;
    GLuint vbo = 0;

    QuadVAO() {
        float quad_vertices[] = {
            // positions   // texcoords
            0.0f, 1.0f,   0.0f, 1.0f,
            1.0f, 0.0f,   1.0f, 0.0f,
            0.0f, 0.0f,   0.0f, 0.0f,
            0.0f, 1.0f,   0.0f, 1.0f,
            1.0f, 1.0f,   1.0f, 1.0f,
            1.0f, 0.0f,   1.0f, 0.0f
        };

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    ~QuadVAO() {
        if (vbo) glDeleteBuffers(1, &vbo);
        if (vao) glDeleteVertexArrays(1, &vao);
    }
};

// Cache de texturas
static std::unordered_map<std::string, GLuint> m_texture_cache;

// Singleton VAO
static std::unique_ptr<QuadVAO> s_quad_vao;

GLuint bkend::get_quad_vao() {
    if (!s_quad_vao)
        s_quad_vao = std::make_unique<QuadVAO>();
    return s_quad_vao->vao;
}

// Função segura para obter/gerar textura
GLuint bkend::opengl3_get_texture(const butil::texture& tex) {
    auto it = m_texture_cache.find(tex.m_path);
    if (it != m_texture_cache.end()) return it->second;

    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (!tex.m_buffer.empty()) {
        GLenum format = tex.m_has_alpha ? GL_RGBA : GL_RGB;
        GLenum internalFormat = tex.m_use_red_channel ? GL_RED : format;

        // cria textura base do tamanho total
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat,
                     (GLsizei)tex.m_size[0] + tex.m_offset[0],
                     (GLsizei)tex.m_size[1] + tex.m_offset[1],
                     0, internalFormat, GL_UNSIGNED_BYTE, nullptr);

        // subimagem
        glTexSubImage2D(GL_TEXTURE_2D, 0,
                        tex.m_offset[0], tex.m_offset[1],
                        (GLsizei)tex.m_size[0], (GLsizei)tex.m_size[1],
                        internalFormat, GL_UNSIGNED_BYTE, tex.m_buffer.data());
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        unsigned char white_pixel[4] = {255, 255, 255, 255};
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, white_pixel);
    }

    m_texture_cache[tex.m_path] = texture_id;
    return texture_id;
}

// Limpa cache de texturas
void bkend::opengl3_clear_texture_cache() {
    for (auto& tex : m_texture_cache) glDeleteTextures(1, &tex.second);
    m_texture_cache.clear();
}

// Setup inicial do OpenGL3
void bkend::set_up_opengl3() {
    if(gladLoadGL())
        std::cout << "OpenGL loaded successfully!" << std::endl;
    else
        std::cout << "Failed to initialize OpenGL context" << std::endl;    

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// Shutdown seguro
void bkend::shutdown_opengl3() {
    opengl3_clear_texture_cache();
    s_quad_vao.reset();
}

// Render principal
void bkend::opengl3_render(butil::draw_data* data) {
    glClearColor(bgui::instance().get_theme().m_clear_color[0],
                 bgui::instance().get_theme().m_clear_color[1],
                 bgui::instance().get_theme().m_clear_color[2],
                 bgui::instance().get_theme().m_clear_color[3]);
    glViewport(0, 0, bos::get_window_size()[0], bos::get_window_size()[1]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glBindVertexArray(get_quad_vao());

    const butil::mat4 proj = bos::get_projection();

    // Agrupamento simples: processa todos os quads
    while (!data->m_quad_requests.empty()) {
        auto call = data->m_quad_requests.front();
        data->m_quad_requests.pop();

        auto* shader = bgl::get_shader_from_tag(call.m_material.m_shader_tag);
        if (!shader) continue;

        shader->bind();

        // bind properties
        for (auto& prop : call.m_material.m_properties)
            shader->set(prop.first, prop.second);

        shader->set("rect", call.m_bounds);
        shader->set("uv_min", call.m_uv_min);
        shader->set("uv_max", call.m_uv_max);
        shader->set("projection", proj);

        if (call.m_material.m_use_tex) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, opengl3_get_texture(call.m_material.m_texture));
            shader->set("tex", 0);
        }

        glDrawArrays(GL_TRIANGLES, 0, call.m_count);

        shader->unbind();
    }

    glBindVertexArray(0);
}