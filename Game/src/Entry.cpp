// Imgui
#include"ImGui/imgui.h"
#include"ImGui/imgui_impl_glfw.h"
#include"ImGui/imgui_impl_opengl3.h"

// OpenGL
#include<GL/glew.h>
#include<GLFW/glfw3.h>

// STL
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// "Engine" core
#include "Core.h"

// Graphics
#include "OpenGL.h"
#include "Model.h"
#include "FPS/Camera.h"

// Input
#include "Mouse.h"
#include "Keyboard.h"



int main()
{
	// Initialize opengl
	init_opengl();
	glfwSetMouseButtonCallback(opengl_handler.window, mouse_button_callback);
	glfwSetCursorPosCallback(opengl_handler.window, cursor_position_callback);
	glfwSetWindowSizeCallback(opengl_handler.window, window_resize_callback);
	glfwSetKeyCallback(opengl_handler.window, key_callback);



	Entity triangle;

	std::string moon_filepath = "res\\earth.obj";

	triangle.geometry = load_mesh(moon_filepath);

	Camera cam;

	// Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(opengl_handler.window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// Variables to be changed in the ImGUI window
	bool draw_model = true;

	bool enable_depth_test = true;
	glEnable(GL_DEPTH_TEST);
	// glEnable(GL_CULL_FACE);

	// Main while loop
	while (!glfwWindowShouldClose(opengl_handler.window) && !keyboard.keys_pressed[GLFW_KEY_ESCAPE])
	{

		cam.update();
		cam.update_opengl_uniforms();

		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Tell OpenGL a new frame is about to begin
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Tell OpenGL which Shader Program we want to use
		glUseProgram(opengl_handler.shader_program);
		// Only draw the triangle if the ImGUI checkbox is ticked
		if (draw_model)
			// Draw the triangle using the GL_TRIANGLES primitive
			triangle.draw();

		// ImGUI window creation
		ImGui::Begin("General options window");
		// Checkbox that appears in the window
		ImGui::Checkbox("Draw model", &draw_model);
		ImGui::Checkbox("Enable Depth test", &enable_depth_test);
		// Ends the window
		ImGui::End();

		if (enable_depth_test) 
		{
			glEnable(GL_DEPTH_TEST);
		}
		else 
		{
			glDisable(GL_DEPTH_TEST);
		}

		// Renders the ImGUI elements
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(opengl_handler.window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Deletes all ImGUI instances
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	finalize_opengl();
}