#pragma once

#include "layerExtensions.hpp"

struct QueueFamilyIndices {

        std::optional<uint32_t> graphicsFamily;

        bool isComplete() { return graphicsFamily.has_value(); }
};

class Device {

public:
        Device() : gpu(VK_NULL_HANDLE) {}

        void enumeratePhysicalDevices(VkInstance instance);
        void createLogicalDevice(void);
        void destroyDevice(void);

        VkPhysicalDevice gpu;
        VkDevice device;
        VkQueue graphicsQueue;
};