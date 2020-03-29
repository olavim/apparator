#pragma once

#include "math.hpp"

namespace apparator {
	struct Material {
		Vector3 ambient;
		Vector3 diffuse;
		Vector3 specular;
		float shininess;

		Material(Vector3 amb, Vector3 dif, Vector3 spec, float s)
			: ambient(amb), diffuse(dif), specular(spec), shininess(s) {};
	};
}
