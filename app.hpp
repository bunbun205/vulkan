#pragma once

#include "window.hpp"
#include "instance.hpp"
#include "device.hpp"

class Application {

public:
	Application(void);
        Application(const std::string name);
        Application(const uint32_t &w, const uint32_t &h);
        Application(const std::string name, const uint32_t &w, const uint32_t &h);
        void run(void);

private:
        void initVulkan(void);
        void mainloop(void);
        void cleanup(void);

private:
        std::string appname;
	Window win;
        Instance inst;
        Device device;
};