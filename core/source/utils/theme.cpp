#include "utils/theme.hpp"

bgui::theme bgui::dark_theme() {
    bgui::theme t;

    // ---------- DEFAULT (from old m_clear_color, m_text_color, m_box_color) ----------
    t.base.visual.background.normal = {0.06f, 0.06f, 0.06f, 1.f};  // m_clear_color
    t.base.visual.text.normal       = {1.f, 1.f, 1.f, 1.f};        // m_text_color
    t.base.visual.border.normal     = {0.04f, 0.04f, 0.04f, 1.f};  // border color

    // ---------- element/PANEL (from old m_box_color) ----------
    t.types["linear"].visual.background.normal = {0.08f, 0.08f, 0.08f, 1.f};  // m_box_color
    t.types["linear"].visual.border.normal = {0.1f, 0.1f, 0.1f, 1.f};
    t.types["linear"].visual.visible = false;
    t.types["linear"].layout.set_padding(5, 2);

    t.types["window"].visual.background.normal = {0.08f, 0.08f, 0.08f, 1.f};  // m_box_color
    t.types["window"].visual.border.normal = {0.1f, 0.1f, 0.1f, 1.f};
    t.types["window"].visual.visible = true;
    t.types["window"].layout.set_padding(0, 0);
    t.types["window"].layout.require_size(400, 300);
    t.classes["window-header"].layout.require_mode(mode::stretch, mode::wrap_content);
    t.classes["window-header"].layout.set_padding(0, 0);
    t.classes["window-header"].visual.background.normal = {0.06f, 0.06f, 0.6f, 1.f};
    t.classes["window-header"].visual.border.normal = {0.f};
    t.classes["window-header"].visual.visible = true;
    t.classes["window-button"].layout.require_mode(mode::wrap_content, mode::wrap_content);
    t.classes["window-button"].visual.background.normal = {0.f};    // m_button_color (released)
    t.classes["window-button"].layout.padding           = {0.f};
    t.classes["window-button"].layout.margin           = {0.f};
    t.classes["window-button"].visual.border.normal  = {0.f}; // m_button_hovered_color

    t.types["element"].visual.background.normal = {0.08f, 0.08f, 0.08f, 1.f};  // m_box_color

    // ---------- BUTTON (from old m_button_color, m_button_border_color, etc.) ----------
    t.types["button"].visual.background.normal = {0.1f, 0.1f, 0.1f, 1.f};    // m_button_color (released)
    t.types["button"].visual.background.hover  = {0.12f, 0.12f, 0.12f, 1.f}; // m_button_hovered_color
    t.types["button"].visual.background.pressed  = {0.12f, 0.12f, 0.12f, 1.f}; // m_button_clicked_color
    t.types["button"].visual.border.normal     = {0.04f, 0.04f, 0.04f, 1.f}; // m_button_border_color
    t.types["button"].visual.border_radius     = 4.f;
    t.types["button"].layout.padding           = {5, 5, 5, 5};
    t.types["button"].visual.border_size      = 1.f;
    t.types["button"].layout.require_mode(mode::stretch, mode::wrap_content);
    
    t.types["inputarea"].visual.background.normal = {0.1f, 0.1f, 0.1f, 1.f};    // m_button_color (released)
    t.types["inputarea"].visual.background.hover  = {0.12f, 0.12f, 0.12f, 1.f}; // m_button_hovered_color
    t.types["inputarea"].visual.background.pressed  = {0.12f, 0.12f, 0.12f, 1.f}; // m_button_clicked_color
    t.types["inputarea"].visual.border.normal     = {0.04f, 0.04f, 0.04f, 1.f}; // m_button_border_color
    t.types["inputarea"].visual.border_radius     = 4.f;
    t.types["inputarea"].layout.padding           = {5, 5, 5, 5};
    t.types["inputarea"].visual.border_size      = 1.f;
    t.types["inputarea"].layout.require_mode(mode::stretch, mode::wrap_content);
    t.classes["inputarea-txt"].layout.require_mode(mode::stretch, mode::wrap_content);

    // ---------- CHECKBOX (from old m_cb_color, m_cb_border_color) ----------
    t.types["checkbox"].visual.background.normal = {0.1f, 0.1f, 0.1f, 1.f};    // m_button_color (released)
    t.types["checkbox"].visual.background.hover  = {0.12f, 0.12f, 0.12f, 1.f}; // m_button_hovered_color
    t.classes["checkbox-box"].visual.background.pressed  = {0.5, 0.5, 0.5, 1.f}; // m_button_clicked_color
    t.classes["checkbox-box"].visual.border_size = 2.f;
    t.classes["checkbox-box"].visual.border_radius     = 4.f;
    t.classes["checkbox-box"].layout.set_margin(5, 5);
    t.types["checkbox"].visual.border.normal     = {0.04f, 0.04f, 0.04f, 1.f}; // m_button_border_color
    t.types["checkbox"].visual.border_radius     = 4.f;
    t.types["checkbox"].layout.padding           = {5, 5, 5, 5};
    t.types["checkbox"].visual.border_size      = 1.f;
    t.types["checkbox"].layout.set_padding(5, 2);
    t.types["checkbox"].layout.require_mode(mode::stretch, mode::wrap_content);
    t.classes["checkbox-txt"].layout.require_mode(mode::stretch, mode::wrap_content);
    t.classes["checkbox-txt"].layout.align = alignment::end;
    t.classes["checkbox-txt"].layout.set_margin(1, 1);
    t.classes["checkbox-box"].layout.require_mode(mode::same, mode::match_parent);
    t.classes["window-label"].visual.border.normal = {0.f};
    t.classes["window-label"].visual.background.normal = {0.f};
    t.classes["window-label"].layout.align = alignment::center;
    t.classes["window-label"].layout.require_mode(mode::stretch, mode::wrap_content);
    // ----------- TEXT
    t.types["text"].visual.border.normal = {0.f};
    t.types["text"].visual.text.normal = {1.f};
    t.types["text"].visual.background.normal = {0.f};
    t.types["text"].layout.require_mode(mode::wrap_content, mode::wrap_content);
    t.types["text"].layout.align = alignment::center;

    // ---------- CLASSES (optional accent variants) ----------
    t.classes["primary"].visual.background.normal = {0.2f, 0.4f, 0.8f, 1.f};
    t.classes["primary"].visual.background.hover  = {0.3f, 0.5f, 0.9f, 1.f};

    t.classes["danger"].visual.background.normal = {0.8f, 0.2f, 0.2f, 1.f};
    t.classes["danger"].visual.background.hover  = {0.9f, 0.3f, 0.3f, 1.f};

    return t;
}