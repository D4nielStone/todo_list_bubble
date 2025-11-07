// \brief The element is the base class for all GUI parts.

#pragma once
#include <vector>
#include <memory>

class element {
private:
    std::vector<std::unique_ptr<element>> m_children;
    int m_x{0};
    int m_y{0};
    int m_width{0};
    int m_height{0};
public:
    element() = default;
    virtual ~element() = default;

    // \brief setters
    void set_position(int x, int y);
    void set_size(int width, int height);
    void set_x(int x);
    void set_y(int y);
    void set_rect(int x, int y, int width, int height);

    // \brief getters
    int get_x() const;
    int get_y() const;
    int get_width() const;
    int get_height() const;

    virtual void draw() = 0;
    virtual void update() = 0;
};