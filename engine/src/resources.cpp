#include <fstream>
#include <sstream>
#include <string>

#include "shader.hpp"
#include "texture.hpp"
#include "resources.hpp"

namespace apr = apparator;

std::string apr::readFile(std::string filePath) {
	std::string fileData;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		printf("Cannot open file: %s.\n", filePath.c_str());
		return 0;
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
}

apr::Shader *apr::ResourceManager::loadShader(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath) {
	this->shaders[name] = new apr::Shader(vertexShaderPath, fragmentShaderPath);
	return this->shaders[name];
}

apr::Texture *apr::ResourceManager::loadTexture(std::string name, std::string texturePath) {
	this->textures[name] = new apr::Texture(texturePath);
	return this->textures[name];
}
