#include "rendering/VertexArray.h"

VertexArray::VertexArray()
{
	GLCALL(glGenVertexArrays(1, &vertexArrayID));
}

VertexArray::~VertexArray()
{
	GLCALL(glDeleteVertexArrays(1, &vertexArrayID))
}

void VertexArray::bind() const
{
	GLCALL(glBindVertexArray(vertexArrayID));
}

void VertexArray::unbind() const
{
	GLCALL(glBindVertexArray(0));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const IndexBuffer& ib, const VertexBufferLayout& layout)
{
	bind();
	vb.bind();
	ib.bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCALL(glEnableVertexAttribArray(i));
		GLCALL(glVertexAttribPointer(i, element.count, element.type, element.isNormalised, layout.getStride(), (const void*)offset));

		offset += element.count * VertexBufferElement::getSizeOfType(element.type);

	}
}
