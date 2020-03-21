#pragma once

#include <unordered_map>
#include <string>

#include "material.hpp"
#include "texture.hpp"

namespace apparator {
	std::string readFile(std::string filePath);

	class ResourceManager {
		public:
			~ResourceManager();

			Material *loadMaterial(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath);
			Texture *loadTexture(std::string name, std::string texturePath);
		private:
			std::unordered_map<std::string, Material*> materials;
			std::unordered_map<std::string, Texture*> textures;
	};
}
