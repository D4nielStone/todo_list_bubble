/**
 * @class LinearLayout
 * @brief A layout that arranges its child elements in a single direction (horizontal or vertical).
 * @endcode
 */

#pragma once
#include "layout.hpp"

namespace bgui {
    class linear : public layout {
    public:
        linear(const bgui::orientation& ori = bgui::orientation::horizontal);
        ~linear() = default;
    
        void update() override;
        void fit_to_content() override;
        bgui::layout* as_layout() override { return this; }
    };
}// namespace lay