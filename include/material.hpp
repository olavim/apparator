#pragma once

#include <string>
#include <GL/glew.h>

namespace apparator {
	class Material {
		public:
			unsigned int id;

			Material() : id(0) {};
			Material(std::string vertexShaderPath, std::string fragmentShaderPath);
			~Material();

			void bind() const;
			unsigned int uniformLocation(std::string name);
	};
}
