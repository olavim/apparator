#pragma once

#include <unordered_map>
#include <string>

#include "shader.hpp"
#include "texture.hpp"

namespace apparator {
	std::string readFile(std::string filePath);

	class ResourceManager {
		public:
			~ResourceManager();

			Shader *loadShader(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath);
			Texture *loadTexture(std::string name, std::string texturePath);
		private:
			std::unordered_map<std::string, Shader*> shaders;
			std::unordered_map<std::string, Texture*> textures;
	};
}
