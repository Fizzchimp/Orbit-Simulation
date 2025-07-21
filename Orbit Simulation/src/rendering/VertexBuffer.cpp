#include "rendering/VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) : bufferSize(size)
{
	GLCALL(glGenBuffers(1, &bufferID));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
	GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCALL(glDeleteBuffers(1, &bufferID));
}



void VertexBuffer::updateBuffer(const void* data, unsigned int size) const
{
	if (size != bufferSize) 
	{
		__debugbreak(); // Size mismatch
	}

	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
	GLCALL(void* bufferData = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

	if (!bufferData) 
	{
		__debugbreak();
	}
	memcpy(bufferData, data, size);
	GLCALL(glUnmapBuffer(GL_ARRAY_BUFFER));
}

void VertexBuffer::bind() const
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
}


void VertexBuffer::unbind() const
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
