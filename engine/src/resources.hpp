#pragma once

#include <unordered_map>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace apparator {
	std::string readFile(std::string filePath);

	class Shader;
	class Texture;
	class Model;

	class ResourceManager {
		public:
			static ResourceManager& getInstance();

			static Shader* loadShader(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath);
			static Texture* loadTexture(std::string name, std::string texturePath);
			static Texture* loadTexture(std::string texturePath);
			static Model* loadModel(std::string name, std::string modelPath);
		private:
			ResourceManager() = default;
			~ResourceManager();

			ResourceManager(const ResourceManager&) = delete;
			ResourceManager& operator=(const ResourceManager&) = delete;

			std::unordered_map<std::string, Shader*> shaders;
			std::unordered_map<std::string, Texture*> textures;
			std::unordered_map<std::string, Model*> models;
	};
}
