#include <GL/glew.h>
#include <stdio.h>
#include <math.h>

#include "math.hpp"
#include "camera.hpp"

using namespace apparator;

void camera::Camera::move(const math::vec3 &vector) {
	this->position -= vector;
}

void camera::Camera::rotate(const GLfloat horizontal, const GLfloat vertical) {
	this->angle += math::vec3(horizontal, vertical, 0);
}

math::vec3 camera::Camera::forward() {
	return math::vec3(
		cos(this->angle[1]) * sin(this->angle[0]),
		sin(this->angle[1]),
		cos(this->angle[1]) * cos(this->angle[0])
	);
}

math::vec3 camera::Camera::right() {
	return math::vec3(
		sin(this->angle[0] - (M_PI / 2)),
		0,
		cos(this->angle[0] - (M_PI / 2))
	);
}

math::vec3 camera::Camera::up() {
	return math::cross(this->right(), this->forward());
}

math::mat4 camera::Camera::getTransform() {
	math::mat4 view = math::lookAt(this->position, this->position + this->forward(), math::vec3(0, 1, 0));
	return this->projection * view;
}

camera::PerspectiveCamera::PerspectiveCamera(GLfloat fov, GLfloat aspectRatio) {
	this->projection = math::perspective(math::radians(fov), aspectRatio, 0.1, 100);
}

camera::OrtographicCamera::OrtographicCamera(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top) {
	this->projection = math::ortographic(left, right, bottom, top, -100, 100);
}
