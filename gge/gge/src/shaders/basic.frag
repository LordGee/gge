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