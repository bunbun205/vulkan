#include <iostream>
#include <cstdlib>

#include "app.hpp"

std::vector<const char *> layerNames {

	"VK_LAYER_KHRONOS_validation"
};

int main() {

	Application app("Vulkan");

	try {

		app.run();
	} catch (const std::exception &e) {

		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}