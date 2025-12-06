#include <bgui_backend_glfw.hpp>
#include <os/os.hpp>
#include <stdexcept>
#include <iostream>

// Maps to input conversion
static std::unordered_map<int, bgui::input_key> s_glfw_key_reverse_map = {
    {GLFW_MOUSE_BUTTON_LEFT, bgui::input_key::mouse_left},
    {GLFW_MOUSE_BUTTON_RIGHT, bgui::input_key::mouse_right},
    {GLFW_MOUSE_BUTTON_MIDDLE, bgui::input_key::mouse_middle}
};
static std::unordered_map<int, bgui::input_action> s_glfw_action_reverse_map = {
    {GLFW_PRESS, bgui::input_action::press},
    {GLFW_RELEASE, bgui::input_action::release},
    {GLFW_REPEAT, bgui::input_action::repeat}
};

// GLFW Backend functions
GLFWwindow* bgui::set_up_glfw(int width, int height, const char* title, int flags, GLFWmonitor* monitor, GLFWwindow* share) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to init GLFW\n");
    }
    #ifdef BGUI_USE_OPENGL
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #elif BGUI_USE_VULKAN
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    #endif
    GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, share);

    if (!window) {
        throw std::runtime_error("Failed to create window\n");
        glfwTerminate();
    }

    bgui::get_context().m_title = title;
    bgui::get_context().m_size = bgui::vec2i{width, height};
    glfwSetMouseButtonCallback(window, bgui::glfw_mouse_button_callback);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    return window;
}
void bgui::glfw_update(bgui::context &window_io) {
    glfwPollEvents();

    // Gests the window size
    int width, height;
    glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
    window_io.m_size[0] = width;
    window_io.m_size[1] = height;

    // Gests the mouse position
    double x, y;
    glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
    window_io.m_mouse_position = bgui::vec2i{(int)x, (int)y};
}

void bgui::glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    bgui::input_key internal_key = s_glfw_key_reverse_map.at(button);

    bgui::input_action internal_action = static_cast<bgui::input_action>(s_glfw_action_reverse_map.at(action)); 

    bgui::get_context().m_input_map[internal_key] = internal_action;
}
void bgui::shutdown_glfw() {
    glfwDestroyWindow(glfwGetCurrentContext());
    glfwTerminate();
}