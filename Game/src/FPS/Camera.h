#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct Camera
{
	void update();
	void update_opengl_uniforms();

	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up_vector = glm::vec3(0.0f, 1.0f, 0.0f);

	// in radians
	float pitch = 0.0f, head = 0.0f, roll = 0.0f;

};