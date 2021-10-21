#pragma once

#include "layerExtensions.hpp"

class Instance {

public:
        VkResult createInstance(const char *appname);
        void destroyInstance(void);

        VkInstance instance;
        LayerExtensions layerExtension;
};