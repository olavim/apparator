#include <GL/glew.h>
#include <stdio.h>
#include <math.h>

#include "math.hpp"
#include "camera.hpp"

using namespace apparator;

camera::PerspectiveCamera::PerspectiveCamera(GLfloat fov, GLfloat aspectRatio, GLfloat near, GLfloat far) {
	this->projection = math::perspective(math::radians(fov), aspectRatio, near, far);
}

void camera::PerspectiveCamera::move(const math::vec3 &vector) {
	this->position += vector;
}

void camera::PerspectiveCamera::rotate(const GLfloat horizontal, const GLfloat vertical) {
	this->angle += math::vec3(horizontal, vertical, 0);
}

math::mat4 camera::PerspectiveCamera::getTransform() {
	math::vec3 direction(
		cos(this->angle[1]) * sin(this->angle[0]),
		sin(this->angle[1]),
		cos(this->angle[1]) * cos(this->angle[0])
	);

	math::mat4 view = math::lookAt(this->position, this->position + direction, math::vec3(0, 1, 0));
	return this->projection * view;
}
