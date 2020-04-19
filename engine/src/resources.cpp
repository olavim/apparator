#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include "shader.hpp"
#include "texture.hpp"
#include "resources.hpp"
#include "model.hpp"

namespace apr = apparator;

std::string apr::readFile(std::string filePath) {
	std::string fileData;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cout << "Could not open file: " << filePath << std::endl;
		return NULL;
	}

	std::stringstream sstr;
	sstr << fileStream.rdbuf();
	fileData = sstr.str();
	fileStream.close();

	return fileData;
}

apr::ResourceManager::~ResourceManager() {
	for (std::pair<std::string, apr::Shader*> element : this->shaders) {
		delete element.second;
	}
	for (std::pair<std::string, apr::Texture*> element : this->textures) {
		delete element.second;
	}
	for (std::pair<std::string, apr::Model*> element : this->models) {
		delete element.second;
	}
}

apr::Shader *apr::ResourceManager::loadShader(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath) {
	if (this->shaders.find(name) == this->shaders.end()) {
		this->shaders[name] = new apr::Shader(vertexShaderPath, fragmentShaderPath);
		std::cout << "Shader loaded: " << name << std::endl;
	}
	return this->shaders[name];
}

apr::Texture *apr::ResourceManager::loadTexture(std::string name, std::string texturePath) {
	if (this->textures.find(name) == this->textures.end()) {
		this->textures[name] = new apr::Texture(texturePath);
		std::cout << "Texture loaded: " << name << std::endl;
	}
	return this->textures[name];
}

apr::Texture *apr::ResourceManager::loadTexture(std::string texturePath) {
	return this->loadTexture(texturePath, texturePath);
}

apr::Model *apr::ResourceManager::loadModel(std::string name, std::string modelPath) {
	if (this->models.find(name) == this->models.end()) {
		this->models[name] = new apr::Model(modelPath, *this);
		std::cout << "Model loaded: " << name << std::endl;
	}
	return this->models[name];
}
