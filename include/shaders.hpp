#ifndef SHADERS_HPP
#define SHADERS_HPP

#include <GL/glew.h>

namespace apparator {
	namespace shaders {
		class ShaderProgram {
				GLuint programId;
			public:
				ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
				void use();
		};
	}
}

#endif
