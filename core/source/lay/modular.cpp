
#include "lay/modular.hpp"
#include "bgui.hpp"
using namespace bgui;
    
modular::modular(const orientation& ori) : m_orientation(ori) {
    style.visual.visible = false;
    type = "modular";
}

void modular::on_update() {
}