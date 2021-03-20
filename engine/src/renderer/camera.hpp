#pragma once

#include "../math/mat4.hpp"
#include "../math/transform.hpp"

namespace apparator {
	class Camera {
		public:
			Matrix4 matrix() const;
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
