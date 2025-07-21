#pragma once

class mat2
{
private:
	int rows = 2;
	int cols = 2;

	float m[4];

public:
	// Constructor with 4 values
	mat2(
		float x0, float y0,
		float x1, float y1
	)
	{
		m[0] = x0, m[1] = y0,
			m[2] = x1, m[3] = y1;
	}
	// Default constructor
	mat2() :
		m{
		1.0f, 0.0f,
		0.0f, 1.0f
	} {
	}

	float getValue(int row, int col) const
	{
		return m[col * rows + row];
	}

	// Changes the value of one element in the matrix
	void setValue(int row, int col, float value)
	{
		m[col * rows + row] = value;
	}


	mat2 operator*(const mat2& other) const
	{
		mat2 result;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
				result.m[i * cols + j] =
				m[i * cols + 0] * other.m[0 * cols + j] +
				m[i * cols + 1] * other.m[1 * cols + j];
		}
		return result;
	}

	// Type casting
	operator const float* () const
	{
		return m;
	}
};



mat2 operator*(const float& scalar, const mat2& matrix)
{
	mat2 result;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			result.setValue(i, j, matrix.getValue(i, j) * scalar);
		}
	}
	return result;
}