#version 330 core

smooth in vec3 out_position;
smooth in vec3 out_normal;
smooth in vec2 out_tex_coords;

out vec4 FragColor;

uniform vec4 color;

uniform mat4 view_matrix;

struct Light
{
	vec4 position;
	vec4 color;
};

#define MAX_LIGHTS 10

uniform LightUBlock
{
	Light uLights[MAX_LIGHTS];
};

uniform uint uLightCount;

void main()
{
	vec3 l_pos = (view_matrix  * vec4(10000.0f, 0.0f, 0.0f, 0.0f)).xyz;

	vec3 L = normalize(l_pos);
	float NdotL = max(0.0, dot(normalize(out_normal), L));

   FragColor = color * NdotL;
}