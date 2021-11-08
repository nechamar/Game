#include "Mouse.h"
#include "boost/log/trivial.hpp"
#include "OpenGL.h"

bool IMGUI_mouse = true;

Mouse mouse;

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) 
{
	if (mouse.centered_mouse) 
	{
		mouse.dx = xpos - opengl_handler.window_width / 2;
		mouse.dy = ypos - opengl_handler.window_height / 2;
		glfwSetCursorPos(window, opengl_handler.window_width / 2, opengl_handler.window_height / 2);

	}
	else
	{
		mouse.posx = xpos;
		mouse.posy = ypos;
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	switch (button) 
	{
		case GLFW_MOUSE_BUTTON_LEFT:
		{
			if (action == GLFW_PRESS)
			{
				mouse.left_button_pressed = true;
				// BOOST_LOG_TRIVIAL(info) << "Left button pressed!\n";
			}
			else if (action == GLFW_RELEASE)
			{
				mouse.left_button_pressed = false;
			}
			break;
		}
		case GLFW_MOUSE_BUTTON_RIGHT:
		{
			if (action == GLFW_PRESS)
			{
				mouse.right_button_pressed = true;
				// BOOST_LOG_TRIVIAL(info) << "Right button pressed!\n";
			}
			else if (action == GLFW_RELEASE)
			{
				mouse.right_button_pressed = false;
			}
			break;
		}
		default:
		{

		}

	}
}