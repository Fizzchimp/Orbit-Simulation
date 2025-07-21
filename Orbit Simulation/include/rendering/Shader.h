#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

#include "GL/glew.h"
#include "Errors.h"

class Shader
{
private:
	unsigned int shaderID;
	std::string vertexPath;
	std::string fragmentPath;

	// Cache system to store uniform locations
	mutable std::unordered_map<std::string, int> uniformCache;


public:
	// Creates shader object
	Shader(const char* vertexPath, const char* fragmentPath);

	// Deletes shader program
	~Shader();

	// Read the shader file
	std::string readFile(const char* filePath);

	// Compiles the shader source code
	unsigned int compileShader(unsigned int type, const std::string& source) const;


	// Gets the location of a uniform
	int getUniform(const char* name) const;

	// Set uniforms for different types
	void setUniform1i(const char* name, int value) const; // Integer
	void setUniform1f(const char* name, float value) const; // Float
	void setUniformVec3f(const char* name, const float* vector) const; // Vec3
	void setUniformMat4f(const char* name, const float* matrix) const; // Mat4

	// Binds the shader
	void bind() const;

	// Binds null shader
	void unbind() const;
};