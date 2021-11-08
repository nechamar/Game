#pragma once
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <math.h>
#include "glm/glm.hpp"
#include <vector>
#include "Loader.h"


class Entity
{
public:
	Entity();
	~Entity();

	void draw();
	void update_opengl_uniforms();

	Model* geometry;

	float head = 0.0f, pitch = 0.0f, roll = 0.0f;	// Angles in radians
	glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(.1f, .1f, .1f);;

	//********************************
	//			TEMPORARY
	//********************************
	float color[4] = {1.0f, .0f, .0f, .0f};


};

