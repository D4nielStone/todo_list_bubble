#include <iostream>
#include "tlb.hpp"

void TLB::initGraphics() {
    std::cout << breset << "TLB::" << bgreen << "Initializating graphics\n";
    // step 1: create main window.
    if (!glfwInit()) {
        throw std::runtime_error("Glfw initialization");
    }
    // step 2: create window
    auto* window = glfwCreateWindow(500, 800, "TLB::TodoListBubble", NULL, NULL);
    if (!window) {
        throw std::runtime_error("Invalid Window");
    };

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Glad initializtion");
    }

}
