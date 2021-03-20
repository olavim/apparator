#pragma once

#include "mat4.hpp"
#include "vector3.hpp"

namespace apparator {
	class Vector4 {
			float arr[4];
		public:
			Vector4();
			Vector4(float a, float b, float c, float d);
			Vector4(const Vector4 &vector);
			Vector4(const Vector3 &vector, float d);
			Vector4(float d, const Vector3 &vector);

			float magnitude();
			float magnitude() const;

			Vector4 &operator = (const Vector4 &rhs) = default;

			float &operator [] (int index);
			const float &operator [] (int index) const;

			Vector4 &operator *= (float scalar);
			Vector4 &operator += (const Vector4 &vector);
			Vector4 &operator -= (const Vector4 &vector);
			Vector4 &operator - ();
	};

	Vector4 operator * (Vector4 lhs, float scalar);
	float operator * (Vector4 lhs, const Vector4 &column);
	Vector4 operator + (Vector4 lhs, const Vector4 &vector);
	Vector4 operator - (Vector4 lhs, const Vector4 &vector);
	Vector4 operator * (Matrix4 lhs, const Vector4 &columnVector);
}
