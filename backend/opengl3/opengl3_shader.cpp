#include <string>
#include <map>
#include <utility>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <opengl3/opengl3_shader.hpp>

static std::map<std::pair<std::string, std::string>, std::shared_ptr<GLuint>> opengl3_shader_cache;
static std::map<std::string, std::string> embedded_opengl3_shaders = {
    {"ui::default_vs", R"(#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aUv;

out vec2 Uv;

uniform vec4 rect;
uniform mat4 projection;

void main() {
    vec2 pos = aPos * rect.zw + rect.xy;
    Uv = aUv;
    gl_Position =  projection * vec4(pos, 0, 1);
    })"},
    {"ui::default_fs", R"(#version 330 core

in vec2 Uv; // UV coordinates from vertex opengl3_shader (0..1)
out vec4 FragColor;

// uniforms
uniform vec4 bg_color;
uniform vec4 border_color;
uniform bool bordered;
uniform float border_radius;
uniform float border_size;
uniform vec4 rect;

void main() {
    if(bordered) {
        vec2 pos = rect.zw * Uv;
        vec2 halfSize = rect.zw / 2;
        vec2 center = rect.zw * 0.5;
    vec2 p = pos - center;

    vec2 q = abs(p) - (center - vec2(border_radius));
    float dist = length(max(q, 0.0)) + min(max(q.x, q.y), 0.0) - border_radius;

        if(dist > 0.0) discard;
        if (dist > -border_size && bordered) {
            FragColor = border_color;
        } else {
            FragColor = bg_color;
        }
    } else {
        FragColor = bg_color;
    }
    })"}, {"ui::text_fs", R"(#version 330 core

in vec2 Uv;
out vec4 FragColor;

uniform sampler2D tex;
uniform vec4 text_color;     // RGBA text color
uniform vec2 uv_min;
uniform vec2 uv_max;

void main() {
    vec2 uv = mix(uv_min, uv_max, vec2(Uv.x, 1.0-Uv.y));

    vec4 dist = texture(tex, uv);
    FragColor = dist;
})"}
};

using namespace bgl;

opengl3_shader::opengl3_shader(const char * vertex_path, const char * fragment_path) {
    compile(vertex_path, fragment_path);
}

void opengl3_shader::compile(const char* vertex_path, const char* fragment_path) {
    auto key = std::make_pair(std::string(vertex_path) + "_vs", std::string(fragment_path) + "_fs");

    auto it = opengl3_shader_cache.find(key);
    if (it != opengl3_shader_cache.end()) {
        m_program = opengl3_shader_cache.at(key);
        return;
    }

    // Uses default opengl3_shader if don't found in embedded opengl3_shaders
    auto source_v = embedded_opengl3_shaders.find(key.first) != embedded_opengl3_shaders.end() ? embedded_opengl3_shaders[key.first] : embedded_opengl3_shaders["ui::default_vs"];
    auto source_f = embedded_opengl3_shaders.find(key.second) != embedded_opengl3_shaders.end() ? embedded_opengl3_shaders[key.second] : embedded_opengl3_shaders["ui::default_fs"];
    GLuint vert = compile(GL_VERTEX_SHADER, source_v);
    GLuint frag = compile(GL_FRAGMENT_SHADER, source_f);

    GLuint program = link(vert, frag);
    m_program = std::shared_ptr<GLuint>(new GLuint(program), [](GLuint* p) {
        glDeleteProgram(*p);
        delete p;
    });

    opengl3_shader_cache[key] = m_program;
}

opengl3_shader::~opengl3_shader() {
}

GLuint opengl3_shader::compile(GLenum type, const std::string &source) {
    GLuint opengl3_shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(opengl3_shader, 1, &src, nullptr);
    glCompileShader(opengl3_shader);

    GLint success;
    glGetShaderiv(opengl3_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(opengl3_shader, 512, nullptr, infoLog);
        throw std::runtime_error(
            std::string("opengl3_shader compilation failed (") + 
            (type == GL_VERTEX_SHADER ? "vertex" : "fragment") +
            "): " + infoLog
        );

    }

    return opengl3_shader;
 }

 GLuint opengl3_shader::link(GLuint vert, GLuint frag) {
    GLuint m_id = glCreateProgram();
    glAttachShader(m_id, vert);
    glAttachShader(m_id, frag);
    glLinkProgram(m_id);

    GLint success;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
        throw std::runtime_error("opengl3_shader link failed:\n" + std::string(infoLog));
    }

    glDeleteShader(vert);
    glDeleteShader(frag);

    return m_id;
}

void bgl::opengl3_shader::set(const std::string& name, const butil::propertie u) {
    switch (u.m_type) {
    case 0x0: // vec2
        set_vec2(name.c_str(), u.m_value.m_vec2);
        break;
    case 0x1: // vec3
        set_vec3(name.c_str(), u.m_value.m_vec3);
        break;
    case 0x2: // vec4
        set_vec4(name.c_str(), u.m_value.m_vec4);
        break;
    case 0x3: // mat4
        set_mat4(name.c_str(), u.m_value.m_mat4);
        break;
    case 0x4: // float
        set_float(name.c_str(), u.m_value.m_float);
        break;
    case 0x5: // int
        set_int(name.c_str(), u.m_value.m_int);
        break;
    
    default:
        break;
    }
}
void opengl3_shader::set_mat4(const char *name, const butil::mat4 matrix) {
    GLint loc = glGetUniformLocation(*m_program, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, matrix.data());
}

void opengl3_shader::set_vec4(const char *name, const butil::vec4 vector) {
    GLint loc = glGetUniformLocation(*m_program, name);
    glUniform4f(loc, vector[0], vector[1], vector[2], vector[3]);
}

void opengl3_shader::set_vec3(const char *name, const butil::vec3 vector) {
    GLint loc = glGetUniformLocation(*m_program, name);
    glUniform3f(loc, vector[0], vector[1], vector[2]);
}

void opengl3_shader::set_vec2(const char *name, const butil::vec2 vector) {
    GLint loc = glGetUniformLocation(*m_program, name);
    glUniform2f(loc, vector[0], vector[1]);
}
    
void opengl3_shader::set_bool(const char* name, const bool v) {
    GLint loc = glGetUniformLocation(*m_program, name);
    glUniform1i(loc, v);
}
        
void opengl3_shader::set_int(const char* name, const int v) {
    GLint loc = glGetUniformLocation(*m_program, name);
    glUniform1i(loc, v);
}        

void opengl3_shader::set_float(const char* name, const float v) {
    GLint loc = glGetUniformLocation(*m_program, name);
    glUniform1f(loc, v);
}

void opengl3_shader::bind() {
    if(!m_program || *m_program == 0) {
        throw std::runtime_error("opengl3_shader program is null! Have you compiled before binding?\n");
        return;
    }
    glUseProgram(*m_program);
}

void opengl3_shader::unbind() {
    glUseProgram(0);
}

opengl3_shader* bgl::get_default_opengl3_shader() {
    static opengl3_shader default_opengl3_shader("ui::default", "ui::default");
    return &default_opengl3_shader;
}

opengl3_shader* bgl::get_text_opengl3_shader() {
    static opengl3_shader text_opengl3_shader("ui::default", "ui::text");
    return &text_opengl3_shader;
}

opengl3_shader* bgl::get_opengl3_shader_from_tag(const std::string& name) {
    if(name == "ui::default") {
        return bgl::get_default_opengl3_shader();
    } else if(name == "ui::text") {
        return bgl::get_text_opengl3_shader();
    } else {
        return bgl::get_default_opengl3_shader();
    }
}