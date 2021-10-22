#include "instance.hpp"

std::vector<const char *> layerNames {

	"VK_LAYER_KHRONOS_validation"
};

VkResult Instance::createInstance(const char *appname) {

        if(!layerExtension.getInstanceLayerProperties()) {

                throw std::runtime_error("Validation layers requested but not available");
        }

        VkApplicationInfo appInfo{};

        appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName   = appname;
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName        = "none";
        appInfo.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion         = VK_API_VERSION_1_2;

        VkDebugUtilsMessengerCreateInfoEXT dbgMsgInfo {};
        layerExtension.populateDebugMessengerCreateInfo(dbgMsgInfo);

        auto extensions = layerExtension.getRequiredExtensions();

        VkInstanceCreateInfo instInfo{};

        instInfo.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instInfo.pNext                   = (VkDebugUtilsMessengerCreateInfoEXT*) &dbgMsgInfo;
        instInfo.pApplicationInfo        = &appInfo;
        instInfo.enabledLayerCount       = (uint32_t)layerNames.size();
        instInfo.ppEnabledLayerNames     = layerNames.size() ? layerNames.data() : NULL;
        instInfo.enabledExtensionCount   = (uint32_t)extensions.size();
        instInfo.ppEnabledExtensionNames = extensions.size() ? extensions.data() : NULL;


        return vkCreateInstance(&instInfo, nullptr, &instance);
}

void Instance::destroyInstance() {

        layerExtension.destroyDebugUtilsMessengerEXT(instance, layerExtension.debugMessenger, nullptr);
        if(instance != VK_NULL_HANDLE) vkDestroyInstance(instance, nullptr);
}