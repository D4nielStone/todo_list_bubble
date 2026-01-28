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

    void style_manager::resolve(
        computed_style& cs,
        const std::string& type,
        const std::vector<std::string>& classes,
        const std::string& id,
        input_state state
    ) {
       merge(cs, get_global(), state);

        // 1. type
        if (auto it = m_types.find(type); it != m_types.end())
            merge(cs, it->second, state);

        // 2. classes
        for (auto& c : classes) {
            if (auto it = m_classes.find(c); it != m_classes.end())
                merge(cs, it->second, state);
        }

        // 3. id
        if (!id.empty()) {
            if (auto it = m_ids.find(id); it != m_ids.end())
                merge(cs, it->second, state);
        }
    }
}