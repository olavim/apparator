#pragma once

#include <glm/glm.hpp>
#include "math.hpp"
#include "transform.hpp"

namespace apparator {
	class Camera {
		public:
			Matrix4 matrix();
			Transform transform;
		protected:
			Matrix4 projection;
	};

	class PerspectiveCamera: public Camera {
		public:
			PerspectiveCamera(float fov, float aspectRatio);
	};

	class OrtographicCamera: public Camera {
		public:
			OrtographicCamera(float left, float right, float bottom, float top);
	};
}
