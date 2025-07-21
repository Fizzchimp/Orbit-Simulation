#pragma once

#include <GL/glew.h>
#include <Errors.h>

class IndexBuffer
{
private:
	unsigned int bufferID;
	unsigned int count;

public:
	// Constructor creates and instantiates index buffer
	IndexBuffer(const unsigned int* data, unsigned int count);

	// Destructor deletes the buffer
	~IndexBuffer();

	// Binds the buffer
	void bind() const;

	// Binds null buffer
	void unbind() const;

	// Get the number of indices in the index buffer
	inline int getCount() const { return count; }
};