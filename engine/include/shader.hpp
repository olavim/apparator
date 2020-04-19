#pragma once

#include <string>
#include <GL/glew.h>
#include "math.hpp"

namespace apparator {
	class Shader {
		public:
			unsigned int id;

			Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
			~Shader();

			void bind() const;
			void setMatrix4(std::string name, const Matrix4& matrix) const;
			void setVector3(std::string name, const Vector3& vector) const;
			void setFloat(std::string name, float value) const;
			void setInt(std::string name, int value) const;
	};
}
