#include <fstream>
#include <sstream>
#include <string>

#include "math.hpp"
#include "transform.hpp"

namespace apr = apparator;

void apr::Transform::translate(float x, float y, float z) {
	this->_translation += vec3(x, y, z);
}

void apr::Transform::scale(float x, float y, float z) {
	this->_scale[0] *= x;
	this->_scale[1] *= y;
	this->_scale[2] *= z;
}

void apr::Transform::setScale(float x, float y, float z) {
	this->_scale[0] = x;
	this->_scale[1] = y;
	this->_scale[2] = z;
}

void apr::Transform::rotate(float x, float y, float z) {
	this->_rotation += vec3(x, y, z);
}

void apr::Transform::setRotation(float x, float y, float z) {
	this->_rotation[0] = x;
	this->_rotation[1] = y;
	this->_rotation[2] = z;
}

const apr::vec3& apr::Transform::translation() {
	return this->_translation;
}

const apr::vec3& apr::Transform::scale() {
	return this->_scale;
}

const apr::vec3& apr::Transform::rotation() {
	return this->_rotation;
}

apr::mat4 apr::Transform::matrix() {
	apr::mat4 translation(
		apr::vec4(1, 0, 0, this->_translation[0]),
		apr::vec4(0, 1, 0, this->_translation[1]),
		apr::vec4(0, 0, 1, this->_translation[2]),
		apr::vec4(0, 0, 0, 1)
	);

	apr::mat4 scale(
		apr::vec4(this->_scale[0], 0, 0, 0),
		apr::vec4(0, this->_scale[1], 0, 0),
		apr::vec4(0, 0, this->_scale[2], 0),
		apr::vec4(0, 0, 0, 1)
	);

	float angleX = this->_rotation[0];
	float angleY = this->_rotation[1];
	float angleZ = this->_rotation[2];

	apr::mat4 rotationX(
		apr::vec4(1, 0, 0, 0),
		apr::vec4(0, cos(angleX), -sin(angleX), 0),
		apr::vec4(0, sin(angleX), cos(angleX), 0),
		apr::vec4(0, 0, 0, 1)
	);

	apr::mat4 rotationY(
		apr::vec4(cos(angleY), 0, sin(angleY), 0),
		apr::vec4(0, 1, 0, 0),
		apr::vec4(-sin(angleY), 0, cos(angleY), 0),
		apr::vec4(0, 0, 0, 1)
	);

	apr::mat4 rotationZ(
		apr::vec4(cos(angleZ), -sin(angleZ), 0, 0),
		apr::vec4(sin(angleZ), cos(angleZ), 0, 0),
		apr::vec4(0, 0, 1, 0),
		apr::vec4(0, 0, 0, 1)
	);

	apr::mat4 rotation = rotationX * rotationY * rotationZ;

	return translation * scale * rotation;
}

apr::vec3 apr::Transform::forward() {
	apr::mat4 mat = this->matrix();
	return apr::vec3(mat[0][2], mat[1][2], mat[2][2]);
}

apr::vec3 apr::Transform::right() {
	apr::mat4 mat = this->matrix();
	return apr::vec3(-mat[0][0], -mat[1][0], -mat[2][0]);
}

apr::vec3 apr::Transform::up() {
	apr::mat4 mat = this->matrix();
	return apr::vec3(mat[0][1], mat[1][1], mat[2][1]);
}
