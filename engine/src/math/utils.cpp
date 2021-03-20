#include <GL/glew.h>
#include <math.h>
#include <stdio.h>

#include "utils.hpp"

namespace apr = apparator;

void apr::printVec(const apr::Vector3 &vec) {
	printf("%f, %f, %f\n", vec[0], vec[1], vec[2]);
}

void apr::printVec(const apr::Vector4 &vec) {
	printf("%f, %f, %f, %f\n", vec[0], vec[1], vec[2], vec[3]);
}

void apr::printMat(const apr::Matrix4 &mat) {
	apr::printVec(apr::Vector4(mat.m[0], mat.m[4], mat.m[8], mat.m[12]));
	apr::printVec(apr::Vector4(mat.m[1], mat.m[5], mat.m[9], mat.m[13]));
	apr::printVec(apr::Vector4(mat.m[2], mat.m[6], mat.m[10], mat.m[14]));
	apr::printVec(apr::Vector4(mat.m[3], mat.m[7], mat.m[11], mat.m[15]));
	printf("\n");
}

float apr::radians(const float angle) {
	return static_cast<float>(M_PI / 180.0f) * angle;
}

float apr::dot(const apr::Vector3 &a, const apr::Vector3 &b) {
	return (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]);
}

apr::Vector3 apr::cross(const apr::Vector3 &a, const apr::Vector3 &b) {
	return apr::Vector3(
		(a[1] * b[2]) - (a[2] * b[1]),
		(a[2] * b[0]) - (a[0] * b[2]),
		(a[0] * b[1]) - (a[1] * b[0])
	);
}

apr::Vector4 apr::normalize(const apr::Vector4 &vector) {
	float mag = vector.magnitude();
	return apr::Vector4(
		vector[0] / mag,
		vector[1] / mag,
		vector[2] / mag,
		vector[3] / mag
	);
}

apr::Vector3 apr::normalize(const apr::Vector3 &vector) {
	float mag = vector.magnitude();

	if (mag < 2e-30) {
		return apr::Vector3(vector);
	}

	return apr::Vector3(
		vector[0] / mag,
		vector[1] / mag,
		vector[2] / mag
	);
}

apr::Matrix4 apr::perspective(float fov, float aspect, float near, float far) {
	return apr::Matrix4(
		1 / (aspect * tanf(fov / 2)), 0, 0, 0,
		0, 1 / tanf(fov / 2), 0, 0,
		0, 0, -(far + near) / (far - near), -1,
		0, 0, -(2 * far * near) / (far - near), 0
	);
}

apr::Matrix4 apr::ortographic(float left, float right, float bottom, float top, float near, float far) {
	return apr::Matrix4(
		2 / (right - left), 0, 0, -(right + left) / (right - left),
		0, 2 / (top - bottom), 0, -(top + bottom) / (top - bottom),
		0, 0, -2 / (far - near), -(far + near) / (far - near),
		0, 0, 0, 1
	);
}

apr::Matrix4 apr::lookAt(const apr::Vector3 &eye, const apr::Vector3 &target, const apr::Vector3 &up) {
	apr::Vector3 zAxis = apr::normalize(eye - target);
	apr::Vector3 xAxis = apr::normalize(apr::cross(apr::normalize(up), zAxis));
	apr::Vector3 yAxis = apr::cross(zAxis, xAxis);

	zAxis *= -1;

	return apr::Matrix4(
		xAxis[0], yAxis[0], zAxis[0], 0,
		xAxis[1], yAxis[1], zAxis[1], 0,
		xAxis[2], yAxis[2], zAxis[2], 0,
		-apr::dot(xAxis, eye), -apr::dot(yAxis, eye), -apr::dot(zAxis, eye), 1
	);
}
