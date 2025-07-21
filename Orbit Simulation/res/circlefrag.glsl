#version 460 core

layout(location = 0) in vec4 fragPos;

layout(location = 0) out vec4 colour;

uniform float radius;
uniform vec3 center;
uniform vec3 circleColour;

void main()
{
	float dist = length(fragPos.xy - center.xy);
    if (dist < radius)
    {
        colour = vec4(circleColour, 1.0);
    }
    else
    {
        colour = vec4(0.0);
    }
}