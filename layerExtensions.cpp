#include "layerExtensions.hpp"

extern std::vector<const char *> layerNames;

bool LayerExtensions::getInstanceLayerProperties(void) {

	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	Layers.resize(layerNames.size());

	for(const char *layer : layerNames) {

		bool layerFound = false;

		for(const auto &layerProperties : availableLayers) {

			if(strcmp(layer, layerProperties.layerName) == 0) {

				layerFound = true;
				break;
			}
		}

		if(!layerFound) return false;
		else {
			Layers.push_back(layer);
		}
	}

	return true;
}

void LayerExtensions::getRequiredExtensions(void) {

	uint32_t extensioncount = 0;
	const char** extensions;

	extensions = glfwGetRequiredInstanceExtensions(&extensioncount);

	Extensions.resize(extensioncount);

	for(int i = 0; i < extensioncount; i++) {

		Extensions.push_back(extensions[i]);
	}

	Extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
}

VkResult LayerExtensions::setupDebugMessenger(VkInstance &instance) {

	VkDebugUtilsMessengerCreateInfoEXT dbgMsgInfo {};

	dbgMsgInfo.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	dbgMsgInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	dbgMsgInfo.messageType     = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	dbgMsgInfo.pfnUserCallback = debugCallback;

	auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

	if(func != nullptr) return func(instance, &dbgMsgInfo, nullptr, &debugMessenger);
	else return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void LayerExtensions::destroyDebugMessenger(VkInstance &instance) {

	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

	if(func != nullptr) func(instance, debugMessenger, nullptr);
}