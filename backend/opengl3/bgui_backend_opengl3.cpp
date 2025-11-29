#include <GL/glew.h>
#include "bgui_backend_opengl3.hpp"

void bkend::opengl3_render(butil::draw_data* data) {
}

void bkend::set_up_opengl3() {
    glewInit();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}