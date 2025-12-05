#include <bgui.hpp>
#include <iostream>

int main() {
    GLFWwindow* window = bgui::set_up_glfw(1280, 720, "BGUI GLFW & gl3 Exemple");
    
    bgui::set_up_gl3();
    bgui::set_up_freetype();

    bgui::set_up();
    bgui::linear& root = bgui::set_layout<bgui::linear>(bgui::orientation::vertical);

    // Adding elements
    auto& panel = root.add<bgui::linear>(bgui::orientation::vertical);
    panel.set_padding(10, 2);
    panel.set_width(bgui::mode::pixel, 300.f);
    panel.set_height(bgui::mode::match_parent);
    panel.set_visible(true);

    auto& txt = panel.add<bgui::text>("Linear Layout Exemple", 0.4f);
    txt.set_width(bgui::mode::match_parent);
    txt.set_alignment(bgui::alignment::center);
    auto& button = panel.add<bgui::button>("Button Exemple", 0.4f, [](){});
    button.set_width(bgui::mode::match_parent);

    // individual alignments
    bgui::apply_theme(bgui::dark_theme);

    while (!glfwWindowShouldClose(window)) {
        bgui::glfw_update(bgui::get_window());           // update events
        bgui::update();                 // update layout
        bgui::gl3_render(
            bgui::get_draw_data()       // render the layout data
        );
        glfwSwapBuffers(window);
    }

    bgui::shutdown_lib();
    bgui::shutdown_gl3();
    bgui::shutdown_freetype();
    bgui::shutdown_glfw();
    return 0;

    return 0;
}