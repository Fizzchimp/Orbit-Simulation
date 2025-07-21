#pragma once

#include "rendering/VertexBuffer.h"
#include "rendering/VertexBufferLayout.h"
#include "rendering/IndexBuffer.h"
#include "Errors.h"

class VertexArray
{
private:
	unsigned int vertexArrayID;

public:
	// Constructor and Destructor
	VertexArray();
	~VertexArray();

	// Bind the current vertex array object
	void bind() const;
	// Binds null vertex array object
	void unbind() const;

	// Add a vertex buffer to the vertex array object
	void addBuffer(const VertexBuffer& vb, const IndexBuffer& id, const VertexBufferLayout& layout);
};