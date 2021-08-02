#version 450 core

//'offset' is an input vertex attribute
layout (location = 0) in vec4 position;
layout (location = 1) in vec3 color;

out vec4 vs_color;
void main(void)
{
	gl_Position = position;
	// Output a fixed value for vs_color
	vs_color = vec4(color, 1.0);
}
