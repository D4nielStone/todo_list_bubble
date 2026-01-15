#pragma once
#include "utils/style.hpp"

namespace bgui {
    template<typename T>
    inline void apply_optional(T& dst, const std::optional<T>& src) {
        if (src) dst = *src;
    }
    inline void merge(computed_layout_style& out, const layout_style& in) {
        apply_optional(out.size_mode, in.size_mode);
        apply_optional(out.margin,    in.margin);
        apply_optional(out.padding,   in.padding);
        apply_optional(out.limit_min, in.limit_min);
        apply_optional(out.limit_max, in.limit_max);
        apply_optional(out.size,       in.size);
        apply_optional(out.align,      in.align);
        apply_optional(out.cross_align,      in.cross_align);
        apply_optional(out.ori,      in.ori);
    }
    inline void merge(
        computed_visual_style& out,
        const visual_style& in,
        input_state state
    ) {
        out.background = in.background.resolve(state, out.background);
        out.border     = in.border.resolve(state, out.border);
        out.text       = in.text.resolve(state, out.text);

        apply_optional(out.border_radius, in.border_radius);
        apply_optional(out.font, in.font);
        apply_optional(out.visible, in.visible);
    }
    inline void merge(
        computed_style& out,
        const style& in,
        input_state state
    ) {
        merge(out.visual, in.visual, state);
        merge(out.layout, in.layout);
    }

    class style_manager {
    public:
        // Register
        void set_default(const style& s);
        void set_type(const std::string& type, const style& s);
        void set_class(const std::string& class_name, const style& s);
        void set_id(const std::string& id, const style& s);

        // Final Resolve
        computed_style resolve(
            const std::string& type,
            const std::vector<std::string>& classes,
            const std::string& id,
            const style& inline_style,
            input_state state
        );  

        // singleton
        static style_manager& get_instance() {
            static style_manager sm;
            return sm;
        }
        style_manager(const style_manager&) = delete;
        style_manager& operator=(const style_manager&) = delete;
    private:
        style_manager() = default;
        ~style_manager() = default;

        style m_default;

        std::unordered_map<std::string, style> m_types;
        std::unordered_map<std::string, style> m_classes;
        std::unordered_map<std::string, style> m_ids;
    };
}