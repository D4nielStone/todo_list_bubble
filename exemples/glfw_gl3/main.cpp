#include <bgui.hpp>
#include <iostream>

int main() {
    // First: setup the window
    GLFWwindow* window = bgui::set_up_glfw(1280, 720, "BGUI GLFW & gl3 Exemple");
    
    // Setup the graphics backend and font backend
    bgui::set_up_gl3();
    bgui::set_up_freetype();

    // Setup the library
    bgui::set_up();

    // Get the root layout
    bgui::layout& root = bgui::get_layout();

    // Build a simple UI
    auto& panel =       root.add<bgui::linear>(bgui::orientation::vertical);
    auto& txt =         panel.add<bgui::text>("Linear Layout Exemple", 0.35f);
    auto& button =      panel.add<bgui::button>("Button Exemple", 0.35f, [](){});
    auto& win =         root.add<bgui::window>("Hello Bubble!");
    auto& context =     win.add<bgui::linear>(bgui::orientation::vertical);
                        context.add<bgui::text>("This is a window widget exemple.", 0.35f);
    auto& cb =          context.add<bgui::checkbox>("Checkbox Exemple", 0.35f);
                        context.add<bgui::checkbox>("Allow the checkbox above", 0.35f, true).set_on_change(
        [&cb](bool checked){
            cb.set_enable(checked);
        });
    auto& txt2 =        context.add<bgui::text>("Centered text", 0.35f);
    auto& button2 =     context.add<bgui::button>("Button inside window", 0.35f, [](){});

/*
    // Set styles
    txt2.style.layout.align = bgui::alignment::center;
    txt2.style.layout.require_width(bgui::mode::stretch);
    panel.style.layout.set_padding(10, 2);
    panel.style.layout.require_width(bgui::mode::pixel, 300.f);
    panel.style.layout.require_height(bgui::mode::match_parent);
    button.style.layout.require_width(bgui::mode::match_parent);
    button.style.layout.align = bgui::alignment::center;
    txt2.style.layout.align = bgui::alignment::center;
    txt2.style.layout.require_width(bgui::mode::stretch);
    panel.style.visual.visible = true;
    panel.style.layout.set_padding(10, 2);
    panel.style.layout.require_width(bgui::mode::pixel, 300.f);
    panel.style.layout.require_height(bgui::mode::match_parent);
    panel.style.visual.visible = true;
    button.style.layout.require_width(bgui::mode::match_parent);
    button.set_alignment(bgui::alignment::center);
*/
    bgui::cascade_style(); // merge the default style with elements style

    while (!glfwWindowShouldClose(window)) {
        bgui::glfw_update(bgui::get_context());           // update events
        bgui::on_update();                 // update layout
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
}