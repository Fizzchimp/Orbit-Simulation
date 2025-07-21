#pragma once
#pragma once

#include <GL/glew.h>
#include "Errors.h"

class VertexBuffer
{
private:
	unsigned int bufferID;
	unsigned int bufferSize; // Size of the buffer in bytes

public:
	// Constructor creates and instantiates vertex buffer
	VertexBuffer(const void* dataLocation, unsigned int size);

	// Destructor deletes the buffer
	~VertexBuffer();


	// Edit the data in the buffer
	void updateBuffer(const void* data, unsigned int size) const;

	// Bind the buffer
	void bind() const;

	// Bind null buffer
	void unbind() const;
};