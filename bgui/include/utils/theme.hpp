#pragma once
#include "vec.hpp"

namespace butil {
    struct theme{
        butil::color m_clear_color;
    };
    
    static theme light_theme = {
        {0.86f, 0.86f, 0.86f, 1.f}
    };
}; // namespace butil