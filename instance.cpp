#include "instance.hpp"

VkResult Instance::createInstance(const char *appname) {

        if(!layerExtension.getInstanceLayerProperties()) {

                throw std::runtime_error("Validation layers requested but not available");
        }

        layerExtension.getRequiredExtensions();

        VkApplicationInfo appInfo{};

        appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName   = appname;
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName        = "none";
        appInfo.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion         = VK_API_VERSION_1_2;

        VkInstanceCreateInfo instInfo{};

        instInfo.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instInfo.pApplicationInfo        = &appInfo;
        instInfo.enabledLayerCount       = (uint32_t)layerExtension.Layers.size();
        instInfo.ppEnabledLayerNames     = layerExtension.Layers.size() ? layerExtension.Layers.data() : NULL;
        instInfo.enabledExtensionCount   = (uint32_t)layerExtension.Extensions.size();
        instInfo.ppEnabledExtensionNames = layerExtension.Extensions.size() ? layerExtension.Extensions.data() : NULL;


        return vkCreateInstance(&instInfo, nullptr, &instance);
}

void Instance::destroyInstance() {

        if(instance != VK_NULL_HANDLE) vkDestroyInstance(instance, nullptr);
}