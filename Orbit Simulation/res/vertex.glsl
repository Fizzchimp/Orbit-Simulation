#version 460 core

layout(location = 0) in vec2 vertPos;

layout(location = 0) out vec4 fragPos;

uniform mat4 projection;

void main()
{
	fragPos = vec4(vertPos, 0.0, 0.0);
	gl_Position = projection * vec4(vertPos, 0.0, 1.0);
}