#pragma once
#include "utils/style.hpp"

namespace bgui {

    template<typename T>
    void merge_optional(std::optional<T>& dst, const std::optional<T>& src) {
        if (src) dst = src;
    }

    inline void merge(layout_style& dst, const layout_style& src) {
        merge_optional(dst.size_mode, src.size_mode);
        merge_optional(dst.margin, src.margin);
        merge_optional(dst.padding, src.padding);
        merge_optional(dst.limit_min, src.limit_min);
        merge_optional(dst.limit_max, src.limit_max);
        merge_optional(dst.size, src.size);
        merge_optional(dst.align, src.align);
    }

    inline void merge(visual_style& dst, const visual_style& src) {
        merge_optional(dst.background.normal,  src.background.normal);
        merge_optional(dst.background.hover,   src.background.hover);
        merge_optional(dst.background.pressed, src.background.pressed);
        merge_optional(dst.background.focused, src.background.focused);
        merge_optional(dst.background.disabled,src.background.disabled);

        merge_optional(dst.border.normal,  src.border.normal);
        merge_optional(dst.text.normal,    src.text.normal);

        dst.border_radius = src.border_radius;
        dst.font          = src.font;
        dst.visible       = src.visible;
    }

    inline void merge(style& dst, const style& src) {
        merge(dst.layout, src.layout);
        merge(dst.visual, src.visual);
    }

    class style_manager {
    public:
        // Register
        void set_default(const style& s);
        void set_type(const std::string& type, const style& s);
        void set_class(const std::string& class_name, const style& s);
        void set_id(const std::string& id, const style& s);

        // Final Resolve
        style resolve(
            const std::string& type,
            const std::vector<std::string>& classes,
            const std::string& id,
            const std::optional<style>& inline_style = std::nullopt
        ) const;

    private:
        style m_default;

        std::unordered_map<std::string, style> m_types;
        std::unordered_map<std::string, style> m_classes;
        std::unordered_map<std::string, style> m_ids;
    };
}