#pragma once
#include "layout.hpp"

class absolute_layout : public layout {
public:
    absolute_layout() = default;
    ~absolute_layout() = default;

    void update() override;
};