#pragma once

#include <glm/glm.hpp>
#include "math.hpp"

namespace apparator {
	namespace camera {
		class Camera {
				math::vec3 position = math::vec3();
				math::vec3 angle = math::vec3(3.14, 0, 0);
			public:
				void move(const math::vec3 &vector);
				void rotate(const GLfloat horizontal, const GLfloat vertical);
				math::vec3 forward();
				math::vec3 right();
				math::vec3 up();
				math::mat4 getTransform();
			protected:
				math::mat4 projection;
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
}
