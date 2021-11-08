#include "Keyboard.h"
#include "Mouse.h"
#include "OpenGL.h"
#include "boost/log/trivial.hpp"

Keyboard keyboard;

void key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods) {
	if (action == GLFW_PRESS) 
	{
		keyboard.keys_pressed[key] = true;
	}
	else if(action == GLFW_RELEASE)
	{
		keyboard.keys_pressed[key] = false;
		if (key == GLFW_KEY_F1)
		{
			mouse.centered_mouse = !mouse.centered_mouse;
			if (mouse.centered_mouse)
			{
				mouse.dx = mouse.dy = 0;
				glfwSetCursorPos(window, opengl_handler.window_width / 2, opengl_handler.window_height / 2);
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);			
				BOOST_LOG_TRIVIAL(info) << "mouse centered";
			}
			else
			{
				mouse.posx = opengl_handler.window_width / 2;
				mouse.posy = opengl_handler.window_height / 2;
				glfwSetCursorPos(window, mouse.posx, mouse.posy);
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				BOOST_LOG_TRIVIAL(info) << "mouse uncentered";
			}
		}
	}
}