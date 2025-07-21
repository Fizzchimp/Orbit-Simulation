#pragma once

#include <cmath>

class mat4
{
private:
	int rows = 4;
	int cols = 4;
	float m[16];

public:
	// Constructor with 16 values
	mat4(
		float x0, float y0, float z0, float w0,
		float x1, float y1, float z1, float w1,
		float x2, float y2, float z2, float w2,
		float x3, float y3, float z3, float w3
	)
	{
		m[0]  = x0, m[1]  = y0, m[2]  = z0, m[3]  = w0,
		m[4]  = x1, m[5]  = y1, m[6]  = z1, m[7]  = w1,
		m[8]  = x2, m[9]  = y2, m[10] = z2, m[11] = w2,
		m[12] = x3, m[13] = y3, m[14] = z3, m[15] = w3;
	}

	// Default constructor
	mat4() :
		m{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	} {
	}

	// Returns the value of one element in the matrix
	float getValue(int row, int col) const
	{
		return m[col * rows + row];
	}

	// Changes the value of one element in the matrixz
	void setValue(int row, int col, float value)
	{
		m[col * rows + row] = value;
	}


	// Method to multiply two matrices

	mat4 operator*(const mat4& other) const
	{
		mat4 result;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
				result.m[i * cols + j] =
				m[i * cols + 0] * other.m[0 * cols + j] +
				m[i * cols + 1] * other.m[1 * cols + j] +
				m[i * cols + 2] * other.m[2 * cols + j] +
				m[i * cols + 3] * other.m[3 * cols + j];
		}
		return result;
	}


	// Type casting
	operator const float* () const
	{
		return m;
	}


	// Rotation matricx generation
	static mat4 rotationMatX(float angle)
	{
		float c = cos(angle);
		float s = sin(angle);
		return mat4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, c, -s, 0.0f,
			0.0f, s, c, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	static mat4 rotationMatY(float angle)
	{
		float c = cos(angle);
		float s = sin(angle);
		return mat4(
			c, 0.0f, s, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			-s, 0.0f, c, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	static mat4 rotationMatZ(float angle)
	{
		float c = cos(angle);
		float s = sin(angle);
		return mat4(
			c, -s, 0.0f, 0.0f,
			s, c, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}
};