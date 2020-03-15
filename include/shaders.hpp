#pragma once

#include <GL/glew.h>

namespace apparator {
	namespace shaders {
		class ShaderProgram {
				GLuint programId;
			public:
				ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
				~ShaderProgram();
				void use();
				GLuint uniformLocation(const char* name);
		};
	}
}
