#pragma once

#include "mat4.hpp"
#include "vector3.hpp"
#include "vector4.hpp"

namespace apparator {
	class Quaternion {
		public:
			static Quaternion delta(Vector3 from, Vector3 to);
			static Quaternion lookAt(Vector3 forward, Vector3 up);

			Quaternion();
			Quaternion(const Vector3& axis, float angleRadians);
			Quaternion(float pitch, float yaw, float roll);

			Matrix4 matrix();
			Matrix4 matrix() const;
			Vector3 euler() const;
			Vector3 axis();
			void normalize();
			void conjugate();

			void set(const Quaternion& quat);
			void set(const Vector3& vector, float w);

			Quaternion &operator *= (const Quaternion &quat);
		private:
			float _x;
			float _y;
			float _z;
			float _w;
	};

	Quaternion operator * (Quaternion lhs, const Quaternion &rhs);
	Vector3 operator * (const Quaternion &quat, const Vector3 &vector);

	void printVec(const Vector3 &vec);
	void printVec(const Vector4 &vec);
	void printMat(const Matrix4 &mat);
}
