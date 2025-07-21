#pragma once

class vec3
{
public:
	float x;
	float y;
	float z;

	// Constructors
	vec3(float x, float y, float z) : x(x), y(y), z(z) {}

	// Type casting
	operator const float* () const
	{
		return &x;
	}
};