#pragma once

#include "math.hpp"
#include "texture.hpp"

namespace apparator {
	enum MaterialType {
		COLORED,
		TEXTURED
	};

	struct Material {
		Vector3 ambientColor;
		Vector3 diffuseColor;
		Vector3 specularColor;
		const Texture* diffuseMap;
		const Texture* specularMap;
		float shininess;
		MaterialType type;

		Material(Vector3 amb, Vector3 dif, Vector3 spec, float s)
			: ambientColor(amb), diffuseColor(dif), specularColor(spec), shininess(s), type(MaterialType::COLORED) {};

		Material(const Texture* dif, const Texture* spec, float s)
			: diffuseMap(dif), specularMap(spec), shininess(s), type(MaterialType::TEXTURED) {};
	};
}
