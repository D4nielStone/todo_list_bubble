#pragma once // precautionary measure
             // set the code of each color
#define bred         "\033[0;31m"
#define bgreen       "\033[0;32m"
#define bblue        "\033[0;34m"
#define breset       "\033[0;0m"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// \brief TLB is the main class. Todo List Bubble
class TLB {
private:
    inline static GLFWwindow* m_window{ nullptr };
public:
    TLB();
    static void initGraphics();
    static void windowLoop();
    static void error(const std::string&);
    static void info(const std::string&);
};
