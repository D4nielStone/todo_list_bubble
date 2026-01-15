/**
 * @class Linear Layout
 * @file linear.hpp
 */

#pragma once
#include "layout.hpp"

namespace bgui {
    class linear : public layout {
    protected:
        orientation m_orientation;
    public:
        linear(const bgui::orientation& ori = bgui::orientation::horizontal);
        ~linear() = default;
    
        void on_update() override;
        float content_height() override;
        float content_width() override;
        
        bgui::layout* as_layout() override { return this; }
    };
}// namespace bgui