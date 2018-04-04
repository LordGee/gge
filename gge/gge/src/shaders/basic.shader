#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix = mat4(1.0f);
uniform mat4 ml_matrix = mat4(1.0f);

out DATA{
	vec4 position;
vec4 color;
} vs_out;

void main() {
	gl_Position = pr_matrix * vw_matrix * ml_matrix * position;
	vs_out.position = ml_matrix * position;
	vs_out.color = color;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 colour;
uniform vec2 light_pos;

in DATA{
	vec4 position;
vec4 color;
} vs_in;

void main() {
	float intensity = 1.0 / length(vs_in.position.xy - light_pos);
	color = vs_in.color * intensity;
};
