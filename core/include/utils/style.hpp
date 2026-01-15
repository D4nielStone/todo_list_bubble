#pragma once
#include "material.hpp"
#include "enums.hpp"
#include "vec.hpp"
#include <optional>

namespace bgui {
    struct layout_style {
        std::optional<vec<2, mode>> size_mode = vec<2, mode>{mode::pixel, mode::pixel};
        std::optional<vec4i> margin = vec4i{0, 0, 0, 0};
        std::optional<vec4i> padding = vec4i{0, 0, 0, 0};
        std::optional<vec2i> limit_min = vec2i{20, 20};
        std::optional<vec2i> limit_max = vec2i{INT_MAX, INT_MAX};
        std::optional<vec2> size = vec2{0.f, 0.f};
        std::optional<alignment> align {alignment::start};


        void set_padding(int a, int b) {
            padding = vec4i{a, b, a, b};
        }

        void require_height(mode m, float v = 100.f) {
            (*size_mode)[1] = m;
            (*size)[1] = v;
        }
        void require_width(mode m, float v = 100.f) {
            (*size_mode)[0] = m;
            (*size)[0] = v;
        }
    };
    
    struct state_color {
        std::optional<color> normal;
        std::optional<color> hover;
        std::optional<color> pressed;
        std::optional<color> focused;
        std::optional<color> disabled;

        color resolve(input_state state, const color& fallback) const {
            if (state == input_state::hover    && hover)    return *hover;
            if (state == input_state::pressed  && pressed)  return *pressed;
            if (state == input_state::focused  && focused)  return *focused;
            if (state == input_state::disabled && disabled) return *disabled;
            if (normal) return *normal;
            return fallback;
        }
    };

    struct visual_style {
        state_color background;
        state_color border;
        state_color text;

        float border_radius = 0.0f;
        std::string font = "default";
        bool visible     = true;
    };
    // \brief Style structure that contains visual and layout styles
    struct style {
        // Layout style parameters
        layout_style layout;
        // Visual style parameters
        visual_style visual;
    };
} // namespace bgui