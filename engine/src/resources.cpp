#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include "renderer/shader.hpp"
#include "renderer/texture.hpp"
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

apr::ResourceManager& apr::ResourceManager::getInstance() {
	static apr::ResourceManager instance;
	return instance;
}

apr::Shader *apr::ResourceManager::loadShader(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath) {
	apr::ResourceManager& mgr = apr::ResourceManager::getInstance();

	if (mgr.shaders.find(name) == mgr.shaders.end()) {
		mgr.shaders[name] = new apr::Shader(vertexShaderPath, fragmentShaderPath);
		std::cout << "Shader loaded: " << name << std::endl;
	}
	return mgr.shaders[name];
}

apr::Texture *apr::ResourceManager::loadTexture(std::string name, std::string texturePath) {
	apr::ResourceManager& mgr = apr::ResourceManager::getInstance();

	if (mgr.textures.find(name) == mgr.textures.end()) {
		mgr.textures[name] = new apr::Texture(texturePath);
		std::cout << "Texture loaded: " << name << std::endl;
	}
	return mgr.textures[name];
}

apr::Texture *apr::ResourceManager::loadTexture(std::string texturePath) {
	return apr::ResourceManager::loadTexture(texturePath, texturePath);
}

apr::Model *apr::ResourceManager::loadModel(std::string name, std::string modelPath) {
	apr::ResourceManager& mgr = apr::ResourceManager::getInstance();

	if (mgr.models.find(name) == mgr.models.end()) {
		mgr.models[name] = new apr::Model(modelPath);
		std::cout << "Model loaded: " << name << std::endl;
	}
	return mgr.models[name];
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
