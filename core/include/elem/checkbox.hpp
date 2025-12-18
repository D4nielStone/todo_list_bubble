#pragma once
#include "elem/text.hpp"
#include "utils/draw.hpp"
#include <functional>

namespace bgui {
    class checkbox : public element {
    private:
        text* m_label; //< Reference to text child
    public:
        /// @brief Simple constructor
        /// @param id Will be processed as a global variable and accessible anytime.
        checkbox(const char* id) : element(id) {};
        ~checkbox() = default;
        
        //void on_clicked() override;
        //void on_released() override;
        //void on_mouse_hover() override;
        //float content_width() override;
        //float content_height() override;
        //void update() override;
        //void get_requests(bgui::draw_data* calls) override;
        void apply_theme(const bgui::theme& t) override;
    };
} // namespace bgui