#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

struct Mouse {
	union {
		double posx = 0.0;
		double dx;
	};
	union {
		double posy = 0.0;
		double dy;
	};
	bool left_button_pressed = false;
	bool right_button_pressed = false;

	bool centered_mouse = false;
};

extern Mouse mouse;

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);