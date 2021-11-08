#pragma once
#include <vector>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

struct Keyboard {
	std::vector<bool> keys_pressed = std::vector<bool>(GLFW_KEY_LAST);
};

extern Keyboard keyboard;

void key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods);