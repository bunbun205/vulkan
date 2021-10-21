#include "window.hpp"

void windowSizeCallback(GLFWwindow *win, int w, int h) {

        glfwSetWindowSize(win, w, h);
}

void windowPosCallback(GLFWwindow *win, int x, int y) {

        glfwSetWindowPos(win, x, y);
}

Window::Window(void) : width(800), height(600) {}

Window::Window(const uint32_t &w, const uint32_t &h) : width(w), height(h) {}

void Window::initWin(void) {

        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        window = glfwCreateWindow(width, height, "Application", nullptr, nullptr);
        glfwSetWindowSizeCallback(window, windowSizeCallback);
        glfwSetWindowPosCallback(window, windowPosCallback);
}

void Window::processInput(void) {

        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, true);
}

void Window::destWin(void) {

        glfwDestroyWindow(window);
        glfwTerminate();
}