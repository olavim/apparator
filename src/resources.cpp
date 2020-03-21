#include <fstream>
#include <sstream>
#include <string>

#include "material.hpp"
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
	for (std::pair<std::string, apr::Material*> element : this->materials) {
		delete element.second;
	}
	for (std::pair<std::string, apr::Texture*> element : this->textures) {
		delete element.second;
	}
}

apr::Material *apr::ResourceManager::loadMaterial(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath) {
	this->materials[name] = new apr::Material(vertexShaderPath, fragmentShaderPath);
	return this->materials[name];
}

apr::Texture *apr::ResourceManager::loadTexture(std::string name, std::string texturePath) {
	this->textures[name] = new apr::Texture(texturePath);
	return this->textures[name];
}
