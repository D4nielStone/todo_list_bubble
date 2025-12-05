/**
 * @class Modular Layout
 * @file modular.hpp
 */

#pragma once
#include "layout.hpp"

namespace bgui {
    class modular : public layout {
    private:
        orientation m_orientation;
    public:
        modular(const bgui::orientation& ori = bgui::orientation::horizontal);
        ~modular() = default;
    
        void update() override;
        void set_orientation(const orientation& ori) { m_orientation = ori; };
        void fit_to_content() override;
        bgui::layout* as_layout() override { return this; }
    };
}// namespace lay