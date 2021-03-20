#pragma once

namespace apparator {
	class Vector2 {
			float arr[2];
		public:
			Vector2();
			Vector2(float a, float b);
			Vector2(const Vector2 &vector);

			float magnitude();
			float magnitude() const;

			Vector2 &operator = (const Vector2 &rhs) = default;

			float &operator [] (const int index);
			const float &operator [] (const int index) const;

			Vector2 &operator *= (float scalar);
			Vector2 &operator += (const Vector2 &vector);
			Vector2 &operator -= (const Vector2 &vector);
			Vector2 &operator - ();
	};

	Vector2 operator * (Vector2 lhs, float scalar);
	float operator * (Vector2 lhsRow, const Vector2 &rhsColumn);
	Vector2 operator + (Vector2 lhs, const Vector2 &rhs);
	Vector2 operator - (Vector2 lhs, const Vector2 &rhs);
}
