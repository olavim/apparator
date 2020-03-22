#include <GL/glew.h>
#include <stdio.h>
#include <math.h>

#include "math.hpp"
#include "camera.hpp"

namespace apr = apparator;

apr::mat4 apr::Camera::matrix() {
	apr::mat4 view = apr::lookAt(
		this->transform.translation(),
		this->transform.translation() + this->transform.forward(),
		this->transform.up()
	);
	return this->projection * view;
}

apr::PerspectiveCamera::PerspectiveCamera(GLfloat fov, GLfloat aspectRatio) {
	this->projection = apr::perspective(radians(fov), aspectRatio, 0.1, 100);
}

apr::OrtographicCamera::OrtographicCamera(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top) {
	this->projection = apr::ortographic(left, right, bottom, top, -100, 100);
}
