#include <iostream>
#include "tlb.hpp"
#include "bgui.hpp"
#include "elem/text.hpp"
#include "elem/button.hpp"
#include "elem/linear_layout.hpp"

GLFWwindow* TLB::m_window = nullptr;

void TLB::config_layout() {
    bgui::instance().init_lib();
    auto& lay = bgui::instance().set_layout<layout>();

    // lateral panel is a linear and vertical layout
    auto& lp = lay.add<linear_layout>(butil::orientation::vertical);
    auto& center = lay.add<linear_layout>(butil::orientation::vertical);

    // sets panel visible
    lp.set_visible(true);
    lp.set_padding(5, 5);

    // set rect manually
    lp.set_rect(0, 0, 200, 1000);
    center.set_rect(200, 0, 1000, 1000);
    auto& top = center.add<linear_layout>(butil::orientation::horizontal);
    top.set_height(50);
    top.get_material().set("u_bg_color", butil::color{0.96f, 0.96f, 0.96f, 1.f});
    center.set_cross_alignment(butil::alignment::stretch);
    top.set_alignment(butil::alignment::center);
    top.add<elements::text>("Home", 0.8f);
    top.set_visible(true);

    // cross alignment (horizontal)
    lp.set_cross_alignment(butil::alignment::stretch);

    // add elements:
    lp.add<elements::text>("Groups", 0.5f);

    lp.add<elements::button>("+ Add a new Group", 0.5f, [&](){
        auto& m = lay.new_modal<linear_layout>(butil::orientation::vertical);
        m.set_cross_alignment(butil::alignment::end);
        m.set_padding(5, 5);
        m.add<elements::text>("Exemple of a modal element:", 0.5f);
        m.add<elements::button>("Close", 0.5f, [&](){
            lay.pop_modal();
        }).set_intern_spacing(5, 5);
        m.set_visible(true);
    }).set_intern_spacing(5, 5);
}

void TLB::error(const std::string &msg) {
    throw std::runtime_error(msg);
}
void TLB::info(const std::string& msg) {
    std::cout << breset << "TLB::" << bgreen << msg << "\n" << breset;
}
void TLB::add_task(const std::string & name) {
    m_tasks.push_back({false, name});
    info("adding task " + name);
}
void TLB::init_graphics() {
    TLB::info("Creating new window...");
    // step 1: init glfw
    if (!glfwInit()) {
        TLB::error("Glfw initialization");
    }
    // step 2: create window and init glad
    
    m_window = glfwCreateWindow(800, 600, "Todo List Bubble v1.0", NULL, NULL);
    if (!m_window) {
        TLB::error("Invalid window");
    };

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        TLB::error("Glad initialization");
    }

    TLB::info("Window created");

    config_layout();
}
void TLB::window_loop() {
    TLB::info("Starting main loop");
    while(!glfwWindowShouldClose(m_window)) {
        // poll events
        glfwPollEvents();

        // --- //
        // renderingd
        bgui::instance().clear();

        bgui::instance().update();
        bgui::instance().render();
        // --- //

        // swap buffers
        glfwSwapBuffers(m_window);
    }
}