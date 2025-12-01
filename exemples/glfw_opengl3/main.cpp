#include <bgui.hpp>
#include <iostream>

int main() {
    GLFWwindow* window = bkend::set_up_glfw(1280, 720, "BGUI GLFW & Opengl3 Exemple");
    
    bkend::set_up_opengl3();
    bkend::set_up_freetype();

    bgui::set_up();

    blay::linear& root = bgui::instance().set_layout<blay::linear>(butil::orientation::vertical);

    // Adding elements
    root.add<belem::text>("Hello World!", 1.f);

    while (!glfwWindowShouldClose(window)) {
        bkend::glfw_update(bos::get_window());           // update events
        bgui::update();                 // update layout
        bkend::opengl3_render(
            bgui::get_draw_data()       // render the layout data
        );
        glfwSwapBuffers(window);
    }

    bgui::shutdown_lib();
    bkend::shutdown_opengl3();
    bkend::shutdown_freetype();
    bkend::shutdown_glfw();
    return 0;

    return 0;
}