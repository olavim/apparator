#include <GL/glew.h>
#include <math.h>
#include <stdio.h>

#include "math.hpp"

namespace apr = apparator;

void apr::printVec(const apr::vec3 &vec) {
	printf("%f, %f, %f\n", vec[0], vec[1], vec[2]);
}

void apr::printVec(const apr::vec4 &vec) {
	printf("%f, %f, %f, %f\n", vec[0], vec[1], vec[2], vec[3]);
}

void apr::printMat(const apr::mat4 &mat) {
	apr::printVec(mat[0]);
	apr::printVec(mat[1]);
	apr::printVec(mat[2]);
	apr::printVec(mat[3]);
	printf("\n");
}

GLfloat apr::radians(const GLfloat angle) {
	return (M_PI / 180) * angle;
}

GLfloat apr::dot(const apr::vec3 &a, const apr::vec3 &b) {
	return (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]);
}

apr::vec3 apr::cross(const apr::vec3 &a, const apr::vec3 &b) {
	return apr::vec3(
		(a[1] * b[2]) - (a[2] * b[1]),
		(a[2] * b[0]) - (a[0] * b[2]),
		(a[0] * b[1]) - (a[1] * b[0])
	);
}

apr::vec4 apr::normalize(const apr::vec4 &vector) {
	GLfloat mag = vector.magnitude();
	return apr::vec4(
		vector[0] / mag,
		vector[1] / mag,
		vector[2] / mag,
		vector[3] / mag
	);
}

apr::vec3 apr::normalize(const apr::vec3 &vector) {
	GLfloat mag = vector.magnitude();
	return apr::vec3(
		vector[0] / mag,
		vector[1] / mag,
		vector[2] / mag
	);
}

apr::mat4 apr::perspective(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far) {
	return apr::mat4(
		apr::vec4(1 / (aspect * tan(fov / 2)), 0, 0, 0),
		apr::vec4(0, 1 / tan(fov / 2), 0, 0),
		apr::vec4(0, 0, -(far + near) / (far - near), -1),
		apr::vec4(0, 0, -(2 * far * near) / (far - near), 0)
	);
}

apr::mat4 apr::ortographic(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far) {
	return apr::mat4(
		apr::vec4(2 / (right - left), 0, 0, -(right + left) / (right - left)),
		apr::vec4(0, 2 / (top - bottom), 0, -(top + bottom) / (top - bottom)),
		apr::vec4(0, 0, -2 / (far - near), -(far + near) / (far - near)),
		apr::vec4(0, 0, 0, 1)
	);
}

apr::mat4 apr::lookAt(const apr::vec3 &eye, const apr::vec3 &target, const apr::vec3 &up) {
	apr::vec3 zAxis = apr::normalize(eye - target);
	apr::vec3 xAxis = apr::normalize(apr::cross(apr::normalize(up), zAxis));
	apr::vec3 yAxis = apr::cross(zAxis, xAxis);

	zAxis *= -1;

	return apr::mat4(
		apr::vec4(xAxis[0], yAxis[0], zAxis[0], 0),
		apr::vec4(xAxis[1], yAxis[1], zAxis[1], 0),
		apr::vec4(xAxis[2], yAxis[2], zAxis[2], 0),
		apr::vec4(-apr::dot(xAxis, eye), -apr::dot(yAxis, eye), -apr::dot(zAxis, eye), 1)
	);
}
