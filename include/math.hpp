#pragma once

#ifndef M_PI
	#define M_PI 3.141592653589793238462643383279502884L
#endif

#include <GL/glew.h>
#include <glm/glm.hpp>

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

	class Vector3 {
			float arr[3];
		public:
			Vector3();
			Vector3(float a, float b, float c);
			Vector3(const Vector3 &vector);

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

	Vector4 operator * (Matrix4 lhs, const Vector4 &columnVector);
	Matrix4 operator * (Matrix4 lhs, const Matrix4 &rhs);

	float radians(const float angle);

	Matrix4 perspective(float fov, float aspect, float near, float far);
	Matrix4 ortographic(float bottom, float top, float left, float right, float near, float far);
	Matrix4 lookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &up);

	float dot(const Vector3 &a, const Vector3 &b);
	Vector3 cross(const Vector3 &a, const Vector3 &b);
	Vector3 normalize(const Vector3 &a);
	Vector4 normalize(const Vector4 &a);

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
