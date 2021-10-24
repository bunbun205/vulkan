#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vulkan/vulkan.hpp>

#include <map>
#include <mutex>
#include <chrono>
#include <thread>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <unistd.h>
#include <iostream>
#include <optional>
#include <stdexcept>