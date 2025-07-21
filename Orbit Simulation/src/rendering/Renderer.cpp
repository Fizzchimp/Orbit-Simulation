#include "rendering/Renderer.h"

Renderer::Renderer(GLFWwindow* window, int width, int height)
	: window(window), vertexBuffer(nullptr, 4 * 2 * sizeof(float)), indexBuffer(satelliteIndices, 2 * 3), shader("res/vertex.glsl", "res/circlefrag.glsl"), center(0.0f, 0.0f, 0.0f), projection()
{
	layout.push<float>(2);
	vertexArray.addBuffer(vertexBuffer, indexBuffer, layout);


	if (width > height)
	{
		projection.setValue(0, 0, (float)height / width);
	}
	else if (width < height)
	{
		projection.setValue(1, 1, (float)width / height);
	}

	shader.bind();
	shader.setUniform1f("radius", 0.3f);
	shader.setUniformVec3f("center", vec3(0.0f, 0.0f, 0.0f));
	shader.setUniformMat4f("projection", projection);
}

Renderer::~Renderer()
{
	GLCALL(glBindVertexArray(0));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GLCALL(glUseProgram(0));
}


void Renderer::draw() const
{
	// Clear the screen
	GLCALL(glClear(GL_COLOR_BUFFER_BIT));

	// Bind vertex array
	vertexArray.bind();

	// Bind index buffer
	//indexBuffer.bind();

	shader.bind();

	// Draw the shape
	GLCALL(glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::drawSatellites(std::vector<Satellite>& satellites)
{
	for (const Satellite& satellite : satellites)
	{
		vec3 position = satellite.getPosition();
		float radius = satellite.getRadius();

		shader.setUniformVec3f("center", position);
		shader.setUniform1f("radius", radius);
		shader.setUniformVec3f("circleColour", satellite.getColour());

		satelliteVertices[0] = position.x - radius, satelliteVertices[1] = position.y - radius; // Bottom left corner
		satelliteVertices[2] = position.x + radius, satelliteVertices[3] = position.y - radius; // Bottom right corner
		satelliteVertices[4] = position.x + radius, satelliteVertices[5] = position.y + radius; //Top right corner
		satelliteVertices[6] = position.x - radius, satelliteVertices[7] = position.y + radius; // Top left corner

		vertexBuffer.updateBuffer(satelliteVertices, 4 * 2 * sizeof(float));

		// Draw the satellite
		GLCALL(glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr));
	}
}
