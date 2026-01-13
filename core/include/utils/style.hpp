#pragma once
#include "material.hpp"
#include "enums.hpp"
#include "vec.hpp"

namespace bgui {

    struct layout_style {
        mode width  = mode::wrap_content;
        mode height = mode::wrap_content;

        vec2 required_size {0, 0};
        vec4i margin  = {0, 0, 0, 0};
        vec4i padding = {0, 0, 0, 0};
        vec2i limit   = {20, 20};

        alignment align = alignment::start;

        void set_padding(int a, int b) {
            padding = vec4i{a, b, a, b};
        }

        void require_height(mode m, float v = 100.f) {
            height = m;
            required_size[1] = v;
        }
        void require_width(mode m, float v = 100.f) {
            width = m;
            required_size[0] = v;
        }
    };

    struct visual_style {
        color background = {0, 0, 0, 0};
        color border     = {0, 0, 0, 0};

        float border_radius = 0.0f;

        color text_color = {1, 1, 1, 1};
        std::string font = "default";
        bool visible     = true;
    };
    struct style {
        layout_style layout;
        visual_style visual;
    };

} // namespace bgui