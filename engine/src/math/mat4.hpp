#pragma once

namespace apparator {
	class Matrix4 {
		public:
			float m[16];

			Matrix4();
			Matrix4(const Matrix4& matrix);
			Matrix4(const float identity);
			Matrix4(
				float e00, float e01, float e02, float e03, float e10, float e11, float e12, float e13,
				float e20, float e21, float e22, float e23, float e30, float e31, float e32, float e33
			);

			void set(
				float e00, float e01, float e02, float e03, float e10, float e11, float e12, float e13,
				float e20, float e21, float e22, float e23, float e30, float e31, float e32, float e33
			);

			bool invert();
			void transpose();

			Matrix4 &operator = (const Matrix4 &rhs) = default;

			Matrix4 &operator *= (const Matrix4 &matrix);
			Matrix4 &operator - ();
	};

	Matrix4 operator * (Matrix4 lhs, const Matrix4 &rhs);
}
