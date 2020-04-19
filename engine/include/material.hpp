#pragma once

#include <string>
#include "math.hpp"

class aiMaterial;

namespace apparator {
	class Texture;
	class ResourceManager;
	class Shader;

	class Material {
		public:
			Vector3 ambientColor;
			Vector3 diffuseColor;
			Vector3 specularColor;
			const Texture* diffuseMap;
			const Texture* specularMap;
			float shininess;
			const Shader* shader;

			Material(const aiMaterial *material, std::string modelDirectory, ResourceManager& resMgr);

			Material(Vector3 amb, Vector3 dif, Vector3 spec, float s, const Shader* sh)
				: ambientColor(amb), diffuseColor(dif), specularColor(spec), diffuseMap(), specularMap(),
					shininess(s), shader(sh) {};

			Material(const Texture* dif, const Texture* spec, float s, const Shader* sh)
				: ambientColor(), diffuseColor(), specularColor(), diffuseMap(dif), specularMap(spec),
					shininess(s), shader(sh) {};
	};
}
