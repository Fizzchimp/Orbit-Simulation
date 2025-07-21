#pragma once

#include <vector>
#include "rendering/VertexBuffer.h"

#include "GL/glew.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	bool isNormalised;

	static unsigned int getSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_UNSIGNED_INT:  return 4;
			case GL_FLOAT:		   return 4;
			case GL_UNSIGNED_BYTE: return 1;
		}
		std::cout << "Error: Unknown type" << std::endl;
		__debugbreak();
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> elements;
	unsigned int stride; // Number of bytes between each vertex attrbute

public:
	VertexBufferLayout()
		: stride(0) {}


	// Unrecognised type
	template<typename T>
	void push(unsigned int count)
	{
		static_assert(false);
	}

	// Adds integers to the layout
	template<>
	void push<unsigned int>(unsigned int count)
	{
		elements.push_back({GL_UNSIGNED_INT, count, false});
		stride += count * 4;
	}

	// Adds floats to the layout
	template<>
	void push<float>(unsigned int count)
	{
		elements.push_back({GL_FLOAT, count, false});
		stride += count * 4;
	}
	// Returns the elements vector
	inline const std::vector<VertexBufferElement>& getElements() const {return elements;}
	// Returns the stride
	inline unsigned int getStride() const {return stride;}

};