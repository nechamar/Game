#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 tex_coords;

smooth out vec3 out_position;
smooth out vec3 out_normal;
smooth out vec2 out_tex_coords;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main()
{
   gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position, 1.0);
   out_position = (view_matrix * model_matrix * vec4(position, 1.0f)).xyz;
   mat3 normal_matrix = mat3(transpose(inverse(model_matrix)));
   out_normal =  normalize((view_matrix * vec4(normal_matrix * normal, 0.0f)).xyz);
   out_tex_coords = tex_coords;
}