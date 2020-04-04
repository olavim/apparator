#include <GL/glew.h>
#include <stdio.h>
#include <math.h>

#include "math.hpp"
#include "camera.hpp"

namespace apr = apparator;

apr::Matrix4 apr::Camera::matrix() const {
	apr::Matrix4 view = this->transform.matrix();
	view.invert();
	return view * this->projection;
}

apr::PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio) {
	this->projection = apr::perspective(radians(fov), aspectRatio, 0.1f, 100.0f);
}

apr::OrtographicCamera::OrtographicCamera(float left, float right, float bottom, float top) {
	this->projection = apr::ortographic(left, right, bottom, top, -100.0f, 100.0f);
}
