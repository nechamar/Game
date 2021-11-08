#include "Camera.h"
#include "GL/glew.h"
#include "OpenGL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Mouse.h"
#include "Keyboard.h"

#include "boost/log/trivial.hpp"

#include "glm/gtc/matrix_transform.hpp"


void Camera::update()
{
	if (!mouse.centered_mouse)
		return;


	const float sensitivity = 0.01f;

	constexpr float pitch_max = glm::pi<float>() / 2.0f - glm::pi<float>() / 2.0f / 90.0f;

	head += mouse.dx * sensitivity;
	mouse.dx = 0;
	pitch -= mouse.dy * sensitivity;
	mouse.dy = 0;

	if (pitch > pitch_max)
		pitch = pitch_max;
	if (pitch < -pitch_max)
		pitch = -pitch_max;

	direction.x = cos(head) * cos(pitch);
	direction.y = sin(pitch);
	direction.z = sin(head) * cos(pitch);
	direction = glm::normalize(direction);

	// BOOST_LOG_TRIVIAL(info) << "direction " << direction.x << ", " << direction.y << ", " << direction.z;
	// BOOST_LOG_TRIVIAL(info) << "position " << position.x << ", " << position.y << ", " << position.z;

	glm::vec3 right_vector = glm::cross(direction, up_vector);

	float acceleration = 1.0f;

	if (keyboard.keys_pressed[GLFW_KEY_LEFT_SHIFT])acceleration = 20.0f;

	if (keyboard.keys_pressed[GLFW_KEY_W]) position += acceleration * 0.1f * direction;
	if (keyboard.keys_pressed[GLFW_KEY_A]) position -= acceleration * 0.1f * right_vector;
	if (keyboard.keys_pressed[GLFW_KEY_S]) position -= acceleration * 0.1f * direction;
	if (keyboard.keys_pressed[GLFW_KEY_D]) position += acceleration * 0.1f * right_vector;
	// TODO: motion



}

void Camera::update_opengl_uniforms()
{
	glm::mat4 view_matrix = glm::lookAt(position, position + direction, up_vector);
	glUniformMatrix4fv(glGetUniformLocation(opengl_handler.shader_program, "view_matrix"), 1, GL_FALSE, glm::value_ptr(view_matrix));
	
	glm::mat4 projection_matrix = glm::perspectiveFov(glm::pi<float>()/2, (float)opengl_handler.window_width, (float)opengl_handler.window_height, 1.0f, 200.0f);
	glUniformMatrix4fv(glGetUniformLocation(opengl_handler.shader_program, "projection_matrix"), 1, GL_FALSE, glm::value_ptr(projection_matrix));

	
}
