#include "os/style_manager.hpp"

namespace bgui {

    void style_manager::set_default(const style& s) {
        m_default = s;
    }

    void style_manager::set_type(const std::string& type, const style& s) {
        m_types[type] = s;
    }

    void style_manager::set_class(const std::string& class_name, const style& s) {
        m_classes[class_name] = s;
    }

    void style_manager::set_id(const std::string& id, const style& s) {
        m_ids[id] = s;
    }

    style style_manager::resolve(
        const std::string& type,
        const std::vector<std::string>& classes,
        const std::string& id,
        const std::optional<style>& inline_style
    ) const {
        style result = m_default;

        // type
        if (auto it = m_types.find(type); it != m_types.end())
            merge(result, it->second);

        // classes
        for (const auto& cls : classes) {
            if (auto it = m_classes.find(cls); it != m_classes.end())
                merge(result, it->second);
        }

        // ID
        if (!id.empty()) {
            if (auto it = m_ids.find(id); it != m_ids.end())
                merge(result, it->second);
        }

        // Inline
        if (inline_style)
            merge(result, *inline_style);

        return result;
    }

}