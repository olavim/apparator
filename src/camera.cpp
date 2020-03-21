#include <GL/glew.h>
#include <stdio.h>
#include <math.h>

#include "math.hpp"
#include "camera.hpp"

namespace apr = apparator;

void apr::Camera::move(const apr::vec3 &vector) {
	this->position -= vector;
}

void apr::Camera::rotate(const GLfloat horizontal, const GLfloat vertical) {
	this->angle += vec3(horizontal, vertical, 0);
}

apr::vec3 apr::Camera::forward() {
	return vec3(
		cos(this->angle[1]) * sin(this->angle[0]),
		sin(this->angle[1]),
		cos(this->angle[1]) * cos(this->angle[0])
	);
}

apr::vec3 apr::Camera::right() {
	return vec3(
		sin(this->angle[0] - (M_PI / 2)),
		0,
		cos(this->angle[0] - (M_PI / 2))
	);
}

apr::vec3 apr::Camera::up() {
	return cross(this->right(), this->forward());
}

apr::mat4 apr::Camera::getTransform() {
	mat4 view = lookAt(this->position, this->position + this->forward(), vec3(0, 1, 0));
	return this->projection * view;
}

apr::PerspectiveCamera::PerspectiveCamera(GLfloat fov, GLfloat aspectRatio) {
	this->projection = perspective(radians(fov), aspectRatio, 0.1, 100);
}

apr::OrtographicCamera::OrtographicCamera(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top) {
	this->projection = ortographic(left, right, bottom, top, -100, 100);
}
