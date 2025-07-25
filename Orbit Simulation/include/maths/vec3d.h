#pragma once

#pragma once
#include <cmath>

#include "vec3.h"

class vec3d
{
public:
	double x;
	double y;
	double z;

	// Constructors
	vec3d(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}


	double magnitude() const
	{
		return sqrt(x * x + y * y + z * z);
	}


	// Type casting
	operator const double* () const
	{
		return &x;
	}

	// Addition operator
	vec3d operator+(const vec3d& other) const
	{
		return vec3d(x + other.x, y + other.y, z + other.z);
	}

	// Subtraction operator
	vec3d operator-(const vec3d& other) const
	{
		return vec3d(x - other.x, y - other.y, z - other.z);
	}

	// Linear Multiplication operator
	vec3d operator*(double scalar) const
	{
		return vec3d(x * scalar, y * scalar, z * scalar);
	}


	// Convert to a float vector
	operator const vec3() const
	{
		return vec3((float)x, (float)y, (float)x);
	}
};