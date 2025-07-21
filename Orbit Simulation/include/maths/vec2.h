#pragma once

class vec2
{
public:
	float& x;
	float& y;

	// Constructors
	vec2(float x = 0, float y = 0) : x(x), y(y)	{}

	// Type casting
	operator const float* () const
	{
		return &x;
	}
};
