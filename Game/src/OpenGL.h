#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"



struct handler {
	GLFWwindow* window;
	GLuint shader_program;
	int window_width = 800, window_height = 800;
};

extern handler opengl_handler;

void window_resize_callback(GLFWwindow* window, int width, int height);

void compile_shaders();
int init_opengl();
void finalize_opengl();