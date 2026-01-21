#include <bgui.hpp>
#include <iostream>

int main() {
    // Setup
    GLFWwindow* window = bgui::set_up_glfw(1280, 720, "BGUI GLFW & gl3 Exemple");
    bgui::set_up_gl3();
    bgui::set_up_freetype();
    bgui::set_up();

    // Configure declarative styles
    auto& sm = bgui::style_manager::get_instance();
    
    // Define class styles
    bgui::style title_style;
    title_style.visual.text = {0.35f};  // font size
    sm.set_class("title", title_style);
    
    bgui::style sidebar_style;
    sidebar_style.layout.set_padding(10, 2);
    sidebar_style.layout.require_width(bgui::mode::pixel, 300.f);
    sidebar_style.layout.require_height(bgui::mode::match_parent);
    sidebar_style.visual.visible = true;
    sm.set_class("sidebar", sidebar_style);
    
    bgui::style full_width_button_style;
    full_width_button_style.layout.require_width(bgui::mode::match_parent);
    full_width_button_style.layout.align = bgui::alignment::center;
    sm.set_class("full-width-btn", full_width_button_style);
    
    bgui::style centered_text_style;
    centered_text_style.layout.align = bgui::alignment::center;
    centered_text_style.layout.require_width(bgui::mode::stretch);
    sm.set_class("centered", centered_text_style);

    // Build UI declaratively
    bgui::layout& root = bgui::get_layout();

    auto& panel = root.add<bgui::linear>(bgui::orientation::vertical);
    panel.add_class("sidebar");
    auto& txt = panel.add<bgui::text>("Linear Layout Exemple", 0.35f);
    txt.add_class("title");
    auto& button = panel.add<bgui::button>("Button Exemple", 0.35f, [](){});
    button.add_class("full_width_btn");
    auto& win = root.add<bgui::window>("Hello Bubble!");
    auto& context = win.add<bgui::linear>(bgui::orientation::vertical);
    context.add<bgui::text>("This is a window widget exemple.", 0.35f);
    auto& cb = context.add<bgui::checkbox>("Checkbox Exemple", 0.35f);
    context.add<bgui::checkbox>("Allow the checkbox above", 0.35f, true)
        .set_on_change([&cb](bool checked){
            cb.set_enable(checked);
        });
    auto& txt2 = context.add<bgui::text>("Centered text", 0.35f);
    txt2.add_class("centered");
    auto& button2 = context.add<bgui::button>("Button inside window", 0.35f, [](){});

    bgui::cascade_style();

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        bgui::glfw_update(bgui::get_context());
        bgui::on_update();
        bgui::gl3_render(bgui::get_draw_data());
        glfwSwapBuffers(window);
    }

    // Cleanup
    bgui::shutdown_lib();
    bgui::shutdown_gl3();
    bgui::shutdown_freetype();
    bgui::shutdown_glfw();
    return 0;
}