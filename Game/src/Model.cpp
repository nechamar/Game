#include "Model.h"
#include "OpenGL.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "ImGui/imgui.h"

Entity::Entity() {

}

Entity::~Entity() {
	// TODO: delete when we use geometry per multiple entiities
	delete geometry;
}

void Entity::draw() {
	// Draw the triangle using the GL_TRIANGLES primitive
	update_opengl_uniforms();

	glBindVertexArray(geometry->meshes[0].VAO);
	glDrawElements(GL_TRIANGLES, 3 * geometry->meshes[0].number_of_triangles, GL_UNSIGNED_INT, 0);

	// ImGUI window creation
	ImGui::Begin("Model options window");

	ImGui::SliderFloat("head", &head, 0, 2*glm::pi<float>());
	ImGui::SliderFloat("pitch", &pitch, 0, 2*glm::pi<float>());
	ImGui::SliderFloat("roll", &roll, 0, 2*glm::pi<float>());

	ImGui::SliderFloat("scale x", &scale.x, -10, 10);
	ImGui::SliderFloat("scale y", &scale.y, -10, 10);
	ImGui::SliderFloat("scale z", &scale.z, -10, 10);

	ImGui::SliderFloat("translation x", &translation.x, -10, 10);
	ImGui::SliderFloat("translation y", &translation.y, -10, 10);
	ImGui::SliderFloat("translation z", &translation.z, -10, 10);

	// Fancy color editor that appears in the window
	ImGui::ColorEdit4("Color", color);
	// Ends the window
	ImGui::End();

}

void Entity::update_opengl_uniforms() {
	glUniform4f(glGetUniformLocation(opengl_handler.shader_program, "color"), color[0], color[1], color[2], color[3]);

	glm::mat4 model_matrix = glm::mat4(1.0f);
	model_matrix = glm::translate(model_matrix, translation);
	model_matrix = glm::rotate(model_matrix, pitch,  glm::vec3(1.0f, 0.0f, 0.0f));
	model_matrix = glm::rotate(model_matrix, head, glm::vec3(0.0f, 1.0f, 0.0f));
	model_matrix = glm::rotate(model_matrix, roll, glm::vec3(0.0f, 0.0f, 1.0f));
	model_matrix = glm::scale(model_matrix, scale);

	glUniformMatrix4fv(glGetUniformLocation(opengl_handler.shader_program, "model_matrix"), 1, GL_FALSE, glm::value_ptr(model_matrix));
}