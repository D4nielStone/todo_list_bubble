#include <bgui.hpp>
#include <iostream>

int main() {
    GLFWwindow* window = bgui::set_up_glfw(1280, 720, "BGUI GLFW & Opengl3 Exemple");
    
    bgui::set_up_opengl3();
    bgui::set_up_freetype();

    bgui::set_up();
    bgui::linear& root = bgui::set_layout<bgui::linear>(bgui::orientation::vertical);
    root.set_cross_alignment(bgui::alignment::center);

    // Adding elements
    root.add<bgui::text>("Hello World!", 0.5f);
    root.add<bgui::text>("Hello World!", 0.5f);
    root.add<bgui::text>("Hello World!", 0.5f);
    bgui::apply_theme(bgui::light_theme);

    while (!glfwWindowShouldClose(window)) {
        bgui::glfw_update(bgui::get_window());           // update events
        bgui::update();                 // update layout
        bgui::opengl3_render(
            bgui::get_draw_data()       // render the layout data
        );
        glfwSwapBuffers(window);
    }

    bgui::shutdown_lib();
    bgui::shutdown_opengl3();
    bgui::shutdown_freetype();
    bgui::shutdown_glfw();
    return 0;

    return 0;
}