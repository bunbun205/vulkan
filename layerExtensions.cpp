#include "layerExtensions.hpp"

extern std::vector<const char *> layerNames;

bool LayerExtensions::getInstanceLayerProperties(void) {

	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for(const char *layer : layerNames) {

		bool layerFound = false;

		for(const auto &layerProperties : availableLayers) {

			if(strcmp(layer, layerProperties.layerName) == 0) {

				layerFound = true;
				break;
			}
		}

		if(!layerFound) return false;
	}

	return true;
}

std::vector<const char *> LayerExtensions::getRequiredExtensions(void) {

	uint32_t extensioncount = 0;
	const char** extensions;

	extensions = glfwGetRequiredInstanceExtensions(&extensioncount);

	std::vector<const char *> Extensions(extensions, extensions + extensioncount);

	Extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

	return Extensions;
}

VkResult LayerExtensions::setupDebugMessenger(VkInstance instance) {

	VkDebugUtilsMessengerCreateInfoEXT dbgMsgInfo {};
	populateDebugMessengerCreateInfo(dbgMsgInfo);

	return createDebugUtilsMessengerEXT(instance, &dbgMsgInfo, nullptr, &debugMessenger);
}

void LayerExtensions::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &dbgMsgInfo) {

	dbgMsgInfo = {};
	dbgMsgInfo.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	dbgMsgInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	dbgMsgInfo.messageType     = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	dbgMsgInfo.pfnUserCallback = debugCallback;
}

VkResult LayerExtensions::createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger){

	auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

	if(func != nullptr) return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	else return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void LayerExtensions::destroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMsgr, const VkAllocationCallbacks* pAllocator) {

	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

	if(func != nullptr) func(instance, debugMsgr, pAllocator);
}