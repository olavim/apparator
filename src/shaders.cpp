#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

#include "file.hpp"
#include "shaders.hpp"

using namespace apparator;

void compileShader(GLuint shaderId, char const* source) {
	glShaderSource(shaderId, 1, &source , NULL);
	glCompileShader(shaderId);

	int infoLogLength;

	// Check for compilation errors
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0) {
		std::vector<char> errorMessage(infoLogLength + 1);
		glGetShaderInfoLog(shaderId, infoLogLength, NULL, &errorMessage[0]);
		printf("Could not compile shader: %s\n", &errorMessage[0]);
	}
}

shaders::ShaderProgram::ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath) {
	this->programId = glCreateProgram();

	// Create the shaders
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexShaderSource = file::read(vertexShaderPath);
	std::string fragmentShaderSource = file::read(fragmentShaderPath);

	// Compile shaders
	compileShader(vertexShaderId, vertexShaderSource.c_str());
	compileShader(fragmentShaderId, fragmentShaderSource.c_str());

	// Link the program
	glAttachShader(this->programId, vertexShaderId);
	glAttachShader(this->programId, fragmentShaderId);
	glLinkProgram(this->programId);

	// Check for linking errors
	int infoLogLength;
	glGetProgramiv(this->programId, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0) {
		std::vector<char> errorMessage(infoLogLength+1);
		glGetProgramInfoLog(this->programId, infoLogLength, NULL, &errorMessage[0]);
		printf("Could not link shaders: %s\n", &errorMessage[0]);
	}

	// Clean up
	glDetachShader(this->programId, vertexShaderId);
	glDetachShader(this->programId, fragmentShaderId);
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
}

shaders::ShaderProgram::~ShaderProgram() {
	glDeleteProgram(this->programId);
}

void shaders::ShaderProgram::use() {
	glUseProgram(this->programId);
}

GLuint shaders::ShaderProgram::uniformLocation(const char* name) {
	return glGetUniformLocation(this->programId, name);
}
