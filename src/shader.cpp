#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <GL/glew.h>

#include "shader.hpp"
#include "resources.hpp"

namespace apr = apparator;

void compileShader(unsigned int shaderId, std::string source) {
	const char* str = source.c_str();
	glShaderSource(shaderId, 1, &str, NULL);
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

apr::Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath) {
	this->id = glCreateProgram();

	// Create the shaders
	unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexShaderSource = apr::readFile(vertexShaderPath);
	std::string fragmentShaderSource = apr::readFile(fragmentShaderPath);

	// Compile shaders
	compileShader(vertexShaderId, vertexShaderSource.c_str());
	compileShader(fragmentShaderId, fragmentShaderSource.c_str());

	// Link the program
	glAttachShader(this->id, vertexShaderId);
	glAttachShader(this->id, fragmentShaderId);
	glLinkProgram(this->id);

	// Check for linking errors
	int infoLogLength;
	glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0) {
		std::vector<char> errorMessage(infoLogLength+1);
		glGetProgramInfoLog(this->id, infoLogLength, NULL, &errorMessage[0]);
		printf("Could not link shaders: %s\n", &errorMessage[0]);
	}

	// Clean up
	glDetachShader(this->id, vertexShaderId);
	glDetachShader(this->id, fragmentShaderId);
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
}

apr::Shader::~Shader() {
	glDeleteProgram(this->id);
}

void apr::Shader::bind() const {
	glUseProgram(this->id);
}

void apr::Shader::setMatrix4(std::string name, const apr::Matrix4& matrix) const {
	unsigned int uniformLocation = glGetUniformLocation(this->id, name.c_str());
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &matrix.m[0]);
}

void apr::Shader::setVector3(std::string name, const apr::Vector3& vector) const {
	unsigned int uniformLocation = glGetUniformLocation(this->id, name.c_str());
	glUniform3fv(uniformLocation, 1, &vector[0]);
}

void apr::Shader::setFloat(std::string name, float value) const {
	unsigned int uniformLocation = glGetUniformLocation(this->id, name.c_str());
	glUniform1f(uniformLocation, value);
}

void apr::Shader::setInt(std::string name, int value) const {
	unsigned int uniformLocation = glGetUniformLocation(this->id, name.c_str());
	glUniform1i(uniformLocation, value);
}
