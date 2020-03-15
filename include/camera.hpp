#pragma once

#include <glm/glm.hpp>
#include "math.hpp"

namespace apparator {
	namespace camera {
		class PerspectiveCamera {
				math::vec3 position = math::vec3();
				math::vec3 angle = math::vec3(3.14, 0, 0);
				math::mat4 projection;
			public:
				PerspectiveCamera(GLfloat fov, GLfloat aspectRatio, GLfloat near, GLfloat far);
				void move(const math::vec3 &vector);
				void rotate(const GLfloat horizontal, const GLfloat vertical);
				math::mat4 getTransform();
		};
	}
}
