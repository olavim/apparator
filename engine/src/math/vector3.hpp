#pragma once

namespace apparator {
	class Vector3 {
			float arr[3];
		public:
			Vector3() : arr{0, 0, 0} {};
			Vector3(float a, float b, float c) : arr{a, b, c} {};
			Vector3(const Vector3 &vector) : arr{vector.arr[0], vector.arr[1], vector.arr[2]} {};

			float magnitude();
			float magnitude() const;

			Vector3 &operator = (const Vector3 &rhs) = default;

			float &operator [] (const int index);
			const float &operator [] (const int index) const;

			Vector3 &operator *= (float scalar);
			Vector3 &operator += (const Vector3 &vector);
			Vector3 &operator -= (const Vector3 &vector);
			Vector3 &operator - ();
	};

	Vector3 operator * (Vector3 lhs, float scalar);
	float operator * (Vector3 lhsRow, const Vector3 &rhsColumn);
	Vector3 operator + (Vector3 lhs, const Vector3 &rhs);
	Vector3 operator - (Vector3 lhs, const Vector3 &rhs);
}
