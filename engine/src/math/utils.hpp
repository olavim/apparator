#pragma once

#ifndef M_PI
	#define M_PI 3.141592653589793238462643383279502884L
#endif

#include "mat4.hpp"
#include "vector3.hpp"
#include "vector4.hpp"

namespace apparator {
	float radians(const float angle);

	Matrix4 perspective(float fov, float aspect, float near, float far);
	Matrix4 ortographic(float bottom, float top, float left, float right, float near, float far);
	Matrix4 lookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &up);

	float dot(const Vector3 &a, const Vector3 &b);
	Vector3 cross(const Vector3 &a, const Vector3 &b);
	Vector3 normalize(const Vector3 &a);
	Vector4 normalize(const Vector4 &a);

	void printVec(const Vector3 &vec);
	void printVec(const Vector4 &vec);
	void printMat(const Matrix4 &mat);
}
