#pragma once

#include <glm/glm.hpp>
#include "math.hpp"
#include "transform.hpp"

namespace apparator {
	class Camera {
		public:
			mat4 matrix();
			Transform transform;
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
