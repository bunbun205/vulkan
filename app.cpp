#include "app.hpp"

Application::Application(void) : appname("App") {}
Application::Application(const std::string name) : appname(name) {}
Application::Application(const uint32_t &w, const uint32_t &h) : win(w, h), appname("App") {}
Application::Application(const std::string name, const uint32_t &w, const uint32_t &h) : win(w, h), appname(name) {}

void Application::run(void) {

        win.initWin();
        initVulkan();
        mainloop();
        cleanup();
}

void Application::initVulkan(void) {

        inst.layerExtension.getInstanceLayerProperties();

        if(inst.createInstance(appname.c_str()) != VK_SUCCESS) {

                throw std::runtime_error("Failed to create instance");
        }

        if(inst.layerExtension.setupDebugMessenger(inst.instance) != VK_SUCCESS) {

                throw std::runtime_error("Failed to setup debug messenger");
        }
}

void Application::mainloop(void) {

        while(!glfwWindowShouldClose(win.window)) {

                win.processInput();
                glfwPollEvents();
        }
}

void Application::cleanup(void) {

        inst.destroyInstance();
        win.destWin();
}