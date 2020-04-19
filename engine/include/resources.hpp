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
			~ResourceManager();

			Shader *loadShader(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath);

			Texture *loadTexture(std::string name, std::string texturePath);
			Texture *loadTexture(std::string texturePath);

			Model *loadModel(std::string name, std::string modelPath);
		private:
			std::unordered_map<std::string, Shader*> shaders;
			std::unordered_map<std::string, Texture*> textures;
			std::unordered_map<std::string, Model*> models;
	};
}
