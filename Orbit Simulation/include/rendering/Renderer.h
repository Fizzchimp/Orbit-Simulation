#pragma once

// GLEW and GLFW must be included before this file can be included
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Errors.h"
#include "rendering/Shader.h"

#include "rendering/VertexBuffer.h"
#include "rendering/VertexBufferLayout.h"
#include "rendering/VertexArray.h"
#include "rendering/IndexBuffer.h"

#include "maths/vec3.h"
#include "maths/mat4.h"

#include "Satellite.h"



class Renderer
{
private:
	GLFWwindow* window;

	// Vertices for rendering satellites
	float satelliteVertices[4 * 2] = {
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f
	};

	// Indices for rendering satellites
	const unsigned int satelliteIndices[2 * 3] = {
		0, 1, 2, // First Triangle
		2, 3, 0  // Second Triangle
	};

	// Vertex array
	VertexArray vertexArray;

	// Vertex Buffer
	VertexBuffer vertexBuffer;
	VertexBufferLayout layout;

	// Index Buffer
	IndexBuffer indexBuffer;


	// Shader program
	Shader shader;

	vec3 center;
	mat4 projection;

public:
	// Instantiates all buffers and shaders
	Renderer(GLFWwindow* window, int width, int height);

	// Destroys all buffers and shader programs
	~Renderer();

	void draw() const;
	void drawSatellites(std::vector<Satellite>& satellites);
	void drawImgui() const;
};