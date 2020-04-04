#pragma once

#include "math.hpp"

namespace apparator {
	class Transform {
		public:
			void translate(float x, float y, float z);
			void translate(const Vector3& position);
			void setTranslation(const Vector3& position);
			void scale(float x, float y, float z);
			void setScale(float x, float y, float z);
			void rotate(const Quaternion& quat);
			void setRotation(const Quaternion& quat);
			Matrix4 matrix() const;
			const Vector3& translation() const;
			const Vector3& scale() const;
			const Quaternion& rotation() const;
			Vector3 forward();
			Vector3 forward() const;
			Vector3 right();
			Vector3 up();

			Vector3 _translation = Vector3();
			Vector3 _scale = Vector3(1, 1, 1);
			Quaternion _rotation = Quaternion(Vector3(0, 0, 0), 1);
	};
}
