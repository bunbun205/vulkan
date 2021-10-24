#include "device.hpp"

std::vector<const char *> layers {

	"VK_LAYER_KHRONOS_validation"
};

static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice gpu) {

	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(gpu, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(gpu, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for(const auto&queueFamily : queueFamilies) {

		if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {

			indices.graphicsFamily = i;
		}

		if(indices.isComplete()) break;

		i++;
	}

	return indices;
}

static int rankDevice(VkPhysicalDevice device) {

	VkPhysicalDeviceProperties gpuProps;
	vkGetPhysicalDeviceProperties(device, &gpuProps);

	VkPhysicalDeviceFeatures gpuFeats;
	vkGetPhysicalDeviceFeatures(device, &gpuFeats);

	int score {};

	if(gpuProps.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) score += 1000;

	score += gpuProps.limits.maxImageDimension2D;

	if(!gpuFeats.geometryShader && !findQueueFamilies(device).isComplete()) return 0;

	return score;
}

void Device::enumeratePhysicalDevices(VkInstance instance) {

	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	std::multimap<int, VkPhysicalDevice> candidates;

	for(const auto &device : devices) {

		candidates.insert(std::make_pair(rankDevice(device), device));
	}

	if(candidates.rbegin()->first > 0) {

		gpu = candidates.rbegin()->second;

	} else {

		throw std::runtime_error("Failed to find a suitable GPU");
	}
}

void Device::createLogicalDevice(void) {

	QueueFamilyIndices indices = findQueueFamilies(gpu);

	VkDeviceQueueCreateInfo queueCreateInfo {};

	float queuePriority = 1.0;

	queueCreateInfo.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
	queueCreateInfo.queueCount       = 1;
	queueCreateInfo.pQueuePriorities = &queuePriority;

	VkPhysicalDeviceFeatures deviceFeatures {};

	VkDeviceCreateInfo createInfo {};

	createInfo.sType                 = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos     = &queueCreateInfo;
	createInfo.queueCreateInfoCount  = 1;
	createInfo.pEnabledFeatures      = &deviceFeatures;
	createInfo.enabledExtensionCount = 0;
	createInfo.enabledLayerCount     = static_cast<uint32_t>(layers.size());
	createInfo.ppEnabledLayerNames   = layers.data();

	if(vkCreateDevice(gpu, &createInfo, nullptr, &device) != VK_SUCCESS) {

                throw std::runtime_error("Failed to create logical device");
        }

	vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
}

void Device::destroyDevice(void) {

	vkDestroyDevice(device, nullptr);
}