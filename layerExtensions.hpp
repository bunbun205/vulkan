#pragma once

#include "headers.hpp"

class LayerExtensions {

public:
        LayerExtensions() {}
        ~LayerExtensions() {}

        bool getInstanceLayerProperties(void);
        void getRequiredExtensions(void);
        VkResult setupDebugMessenger(VkInstance &instance);
        void destroyDebugMessenger(VkInstance &instance);

        std::vector<const char *> Layers;
        std::vector<const char *> Extensions;

        VkDebugUtilsMessengerEXT debugMessenger;

        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {

		std::cerr << "Validation layer: " << pCallbackData->pMessage << std::endl;

		return VK_FALSE;
	}
};