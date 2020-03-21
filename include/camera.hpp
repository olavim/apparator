#pragma once

#include <glm/glm.hpp>
#include "math.hpp"

namespace apparator {
	class Camera {
			vec3 position = vec3();
			vec3 angle = vec3(3.14, 0, 0);
		public:
			void move(const vec3 &vector);
			void rotate(const GLfloat horizontal, const GLfloat vertical);
			vec3 forward();
			vec3 right();
			vec3 up();
			mat4 getTransform();
		protected:
			mat4 projection;
	};

	class PerspectiveCamera: public Camera {
		public:
			PerspectiveCamera(GLfloat fov, GLfloat aspectRatio);
	};

	class OrtographicCamera: public Camera {
		public:
			OrtographicCamera(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top);
	};
}
