#pragma once
#include <cmath>

class vec3
{
public:
	float x;
	float y;
	float z;

	// Constructors
	vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}


	float magnitude() const
	{
		return sqrt(x * x + y * y + z * z);
	}


	// Type casting
	operator const float* () const
	{
		return &x;
	}

	// Addition operator
	vec3 operator+(const vec3& other) const
	{
		return vec3(x + other.x, y + other.y, z + other.z);
	}

	// Subtraction operator
	vec3 operator-(const vec3& other) const
	{
		return vec3(x - other.x, y - other.y, z - other.z);
	}

	// Linear Multiplication operator
	vec3 operator*(float scalar) const
	{
		return vec3(x * scalar, y * scalar, z * scalar);
	}
};