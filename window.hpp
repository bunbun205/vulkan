#pragma once

#include "headers.hpp"

struct Window{

public:
	Window(void);
	Window(const uint32_t &w, const uint32_t &h);

	GLFWwindow *window;
	void initWin(void);
	void destWin(void);
	void processInput(void);

private:
	uint32_t width;
	uint32_t height;
};
