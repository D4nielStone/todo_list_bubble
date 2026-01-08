#pragma once

namespace bgui {
    enum class mode : uint8_t {
        percent,
        pixel,
        match_parent,
        wrap_content,
        stretch,
        same
    };
    enum class orientation : uint8_t {
        vertical,
        horizontal
    };
    enum class alignment : uint8_t {
        start,
        center,
        end
    };
}