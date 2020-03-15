#include <GL/glew.h>
#include <math.h>
#include <stdio.h>

#include "math.hpp"

using namespace apparator;

void math::printVec(const math::vec3 &vec) {
	printf("%f, %f, %f\n", vec[0], vec[1], vec[2]);
}

void math::printVec(const math::vec4 &vec) {
	printf("%f, %f, %f, %f\n", vec[0], vec[1], vec[2], vec[3]);
}

void math::printMat(const math::mat4 &mat) {
	printVec(mat[0]);
	printVec(mat[1]);
	printVec(mat[2]);
	printVec(mat[3]);
	printf("\n");
}

GLfloat math::radians(const GLfloat angle) {
	return (M_PI / 180) * angle;
}

GLfloat math::dot(const math::vec3 &a, const math::vec3 &b) {
	return (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]);
}

math::vec3 math::cross(const math::vec3 &a, const math::vec3 &b) {
	return math::vec3(
		(a[1] * b[2]) - (a[2] * b[1]),
		(a[2] * b[0]) - (a[0] * b[2]),
		(a[0] * b[1]) - (a[1] * b[0])
	);
}

math::vec4 math::normalize(const math::vec4 &vector) {
	GLfloat mag = vector.magnitude();
	return math::vec4(
		vector[0] / mag,
		vector[1] / mag,
		vector[2] / mag,
		vector[3] / mag
	);
}

math::vec3 math::normalize(const math::vec3 &vector) {
	GLfloat mag = vector.magnitude();
	return math::vec3(
		vector[0] / mag,
		vector[1] / mag,
		vector[2] / mag
	);
}

math::mat4 math::perspective(const GLfloat fov, const GLfloat aspect, const GLfloat near, const GLfloat far) {
	return math::mat4(
		math::vec4(1 / (aspect * tan(fov / 2)), 0, 0, 0),
		math::vec4(0, 1 / tan(fov / 2), 0, 0),
		math::vec4(0, 0, -(far + near) / (far - near), -1),
		math::vec4(0, 0, -(2 * far * near) / (far - near), 0)
	);
}

math::mat4 math::lookAt(const math::vec3 &eye, const math::vec3 &target, const math::vec3 &up) {
	math::vec3 zAxis = math::normalize(eye - target);
	math::vec3 xAxis = math::normalize(math::cross(math::normalize(up), zAxis));
	math::vec3 yAxis = math::cross(zAxis, xAxis);

	return math::mat4(
		math::vec4(xAxis[0], yAxis[0], zAxis[0], 0),
		math::vec4(xAxis[1], yAxis[1], zAxis[1], 0),
		math::vec4(xAxis[2], yAxis[2], zAxis[2], 0),
		math::vec4(-math::dot(xAxis, eye), -math::dot(yAxis, eye), -math::dot(zAxis, eye), 1)
	);
}
