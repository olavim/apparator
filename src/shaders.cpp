#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

#include "file.hpp"
#include "shaders.hpp"

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

apparator::shaders::ShaderProgram::ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath) {
	programId = glCreateProgram();

	// Create the shaders
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexShaderSource = apparator::file::read(vertexShaderPath);
	std::string fragmentShaderSource = apparator::file::read(fragmentShaderPath);

	// Compile shaders
	compileShader(vertexShaderId, vertexShaderSource.c_str());
	compileShader(fragmentShaderId, fragmentShaderSource.c_str());

	// Link the program
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	// Check for linking errors
	int infoLogLength;
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0) {
		std::vector<char> errorMessage(infoLogLength+1);
		glGetProgramInfoLog(programId, infoLogLength, NULL, &errorMessage[0]);
		printf("Could not link shaders: %s\n", &errorMessage[0]);
	}

	// Clean up
	glDetachShader(programId, vertexShaderId);
	glDetachShader(programId, fragmentShaderId);
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
}

void apparator::shaders::ShaderProgram::use() {
	glUseProgram(programId);
}
