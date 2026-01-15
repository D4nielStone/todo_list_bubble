/**
 * @class Layout
 * @file layout.hpp
 */

#pragma once
#include "elem/element.hpp"
#include "os/style_manager.hpp"
#include <algorithm>
#include <queue>

namespace bgui {
    class layout : public element {
    protected:
        std::vector<std::unique_ptr<element>> m_elements;
    public:
        layout();
        ~layout() = default;
    
        void mark_children_style_dirty() {
            for (auto& elem : get_elements()) {
                elem->mark_style_dirty();
                
                if (auto* lay = elem->as_layout()) {
                    lay->mark_children_style_dirty();
                }
            }
        }
        void cascade_style() {
            auto& sm = style_manager::get_instance();
                // compute it' style
                computed_style = sm.resolve(
                    type,
                    classes,
                    id,
                    style,
                    m_state
                );
            
            // compute children style
            for (auto& elem : get_elements()) {
                if (elem->is_style_dirty()) {
                    elem->computed_style = sm.resolve(
                        elem->type,
                        elem->classes,
                        elem->id,
                        elem->style,
                        elem->m_state
                    );

                    elem->clear_style_dirty();
                    if(elem->as_layout()) {
                        elem->as_layout()->cascade_style();
                    }
                }
            }
        }
        template<typename T, typename... Args>
        T& add(Args&&... args) {
            auto elem = std::make_unique<T>(std::forward<Args>(args)...);
            T& ref = *elem;
            ref.set_parent(this);
            m_elements.push_back(std::move(elem));
            return ref;
        }
    
        bool remove(element* elem) {
            auto it = std::remove_if(m_elements.begin(), m_elements.end(),
                [elem](const std::unique_ptr<element>& e) { return e.get() == elem; });
            if (it != m_elements.end()) {
                m_elements.erase(it, m_elements.end());
                return true;
            }
            return false;
        }
        void on_update() override;
        void get_requires(bgui::draw_data* calls);
        std::vector<std::unique_ptr<element>>& get_elements();
        bgui::layout* as_layout() override { return this; }
    };
} // namespace bgui