#include <fstream>
#include <sstream>
#include <string>

#include "math.hpp"
#include "transform.hpp"

namespace apr = apparator;

void apr::Transform::translate(float x, float y, float z) {
	this->_translation += Vector3(x, y, z);
}

void apr::Transform::translate(const Vector3& position) {
	this->_translation += this->_rotation * position;
}

void apr::Transform::setTranslation(const Vector3& position) {
	this->_translation[0] = position[0];
	this->_translation[1] = position[1];
	this->_translation[2] = position[2];
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

void apr::Transform::rotate(const apr::Quaternion& quat) {
	this->_rotation = quat * this->_rotation;
	this->_rotation.normalize();
}

void apr::Transform::setRotation(const apr::Quaternion& quat) {
	this->_rotation.set(quat);
	this->_rotation.normalize();
}

const apr::Vector3& apr::Transform::translation() const {
	return this->_translation;
}

const apr::Vector3& apr::Transform::scale() const {
	return this->_scale;
}

const apr::Quaternion& apr::Transform::rotation() const {
	return this->_rotation;
}

apr::Matrix4 apr::Transform::matrix() const {
	apr::Matrix4 translation(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		this->_translation[0], this->_translation[1], this->_translation[2], 1
	);

	apr::Matrix4 scale(
		this->_scale[0], 0, 0, 0,
		0, this->_scale[1], 0, 0,
		0, 0, this->_scale[2], 0,
		0, 0, 0, 1
	);

	apr::Matrix4 rotation = this->_rotation.matrix();
	return rotation * translation * scale;
}

apr::Vector3 apr::Transform::right() {
	return this->_rotation * Vector3(1, 0, 0);
}

apr::Vector3 apr::Transform::up() {
	return this->_rotation * Vector3(0, 1, 0);
}

apr::Vector3 apr::Transform::forward() {
	return this->_rotation * Vector3(0, 0, 1);
}

apr::Vector3 apr::Transform::forward() const {
	return this->_rotation * Vector3(0, 0, 1);
}
