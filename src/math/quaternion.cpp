#include <math.h>
#include <iostream>
#include "math.hpp"

namespace apr = apparator;

apr::Quaternion apr::Quaternion::delta(apr::Vector3 from, apr::Vector3 to) {
	apr::Vector3 fromNormal = apr::normalize(from);
	apr::Vector3 toNormal = apr::normalize(to);
	apr::Vector3 crossProduct = apr::cross(fromNormal, toNormal);

	float s = sqrt(2 * (1 + apr::dot(fromNormal, toNormal)));

	crossProduct *= 1 / s;

	apr::Quaternion quat;
	quat.set(crossProduct, s / 2);
	return quat;
}

apr::Quaternion apr::Quaternion::lookAt(apr::Vector3 forward, apr::Vector3 up) {
	apr::Vector3 normalUp = apr::normalize(up);
	apr::Vector3 v = forward + normalUp * -apr::dot(normalUp, forward);
	apr::Quaternion delta = apr::Quaternion::delta(Vector3(0, 0, 1), v);
	return apr::Quaternion::delta(v, forward) * delta;
}

apr::Quaternion::Quaternion() : _x(0), _y(0), _z(0), _w(1) {}

apr::Quaternion::Quaternion(const apr::Vector3& axis, float angleRadians) {
	apr::Vector3 normal = apr::normalize(axis);

	float s = sin(angleRadians / 2);

	this->_x = normal[0] * s;
	this->_y = normal[1] * s;
	this->_z = normal[2] * s;
	this->_w = cos(angleRadians / 2);
}

apr::Quaternion::Quaternion(float yaw, float pitch, float roll) {
	float c1 = cos(pitch / 2);
	float c2 = cos(yaw / 2);
	float c3 = cos(roll / 2);
	float s1 = sin(pitch / 2);
	float s2 = sin(yaw / 2);
	float s3 = sin(roll / 2);

	this->_w = c1 * c2 * c3 + s1 * s2 * s3;
	this->_x = s1 * c2 * c3 - c1 * s2 * s3;
	this->_y = c1 * s2 * c3 + s1 * c2 * s3;
	this->_z = c1 * c2 * s3 - s1 * s2 * c3;
}

void apr::Quaternion::set(const apr::Quaternion& quat) {
	this->_x = quat._x;
	this->_y = quat._y;
	this->_z = quat._z;
	this->_w = quat._w;
}

void apr::Quaternion::set(const apr::Vector3& vector, float w) {
	this->_x = vector[0];
	this->_y = vector[1];
	this->_z = vector[2];
	this->_w = w;
}

apr::Matrix4 apr::Quaternion::matrix() const {
	float x2 = _x + _x;
	float y2 = _y + _y;
	float z2 = _z + _z;

	float xx2 = _x * x2;
	float yy2 = _y * y2;
	float zz2 = _z * z2;
	float xy2 = _x * y2;
	float xz2 = _x * z2;
	float yz2 = _y * z2;
	float wx2 = _w * x2;
	float wy2 = _w * y2;
	float wz2 = _w * z2;

	return apr::Matrix4(
		1 - yy2 - zz2, xy2 + wz2, xz2 - wy2, 0,
		xy2 - wz2, 1 - xx2 - zz2, yz2 + wx2, 0,
		xz2 + wy2, yz2 - wx2, 1 - xx2 - yy2, 0,
		0, 0, 0, 1
	);
}

apr::Matrix4 apr::Quaternion::matrix() {
	return const_cast<const apr::Quaternion*>(this)->matrix();
}

apr::Vector3 apr::Quaternion::euler() const {
	float x = this->_x;
	float y = this->_y;
	float z = this->_z;
	float w = this->_w;

	return apr::Vector3(
		asin(2 * (y * w - x * z)),
		atan2(2 * (x * w + y * z), 1 - 2 * (x * x + y * y)),
		atan2(2 * (z * w + x * y), 1 - 2 * (y * y + z * z))
	);
}

apr::Vector3 apr::Quaternion::axis() {
	return apr::Vector3(this->_x, this->_y, this->_z);
}

void apr::Quaternion::normalize() {
	float n = (this->_x * this->_x) + (this->_y * this->_y) + (this->_z * this->_z) + (this->_w * this->_w);
	float mult = 1 / sqrt(n);
	this->_x *= mult;
	this->_y *= mult;
	this->_z *= mult;
	this->_w *= mult;
}

void apr::Quaternion::conjugate() {
	this->_x *= -1;
	this->_y *= -1;
	this->_z *= -1;
}

apr::Quaternion &apr::Quaternion::operator *= (const apr::Quaternion& quat) {
	float w = this->_w;
	float x = this->_x;
	float y = this->_y;
	float z = this->_z;
	float w2 = quat._w;
	float x2 = quat._x;
	float y2 = quat._y;
	float z2 = quat._z;

	this->_w = (w * w2) - (x * x2) - (y * y2) - (z * z2);
	this->_x = (w * x2) + (x * w2) + (y * z2) - (z * y2);
	this->_y = (w * y2) - (x * z2) + (y * w2) + (z * x2);
	this->_z = (w * z2) + (x * y2) - (y * x2) + (z * w2);
	return *this;
}

apr::Quaternion apr::operator * (apr::Quaternion lhs, const apr::Quaternion& rhs) {
	lhs *= rhs;
	return lhs;
}

apr::Vector3 apr::operator * (const apr::Quaternion &quat, const apr::Vector3 &vector) {
	apr::Quaternion vectorQuaternion;
	vectorQuaternion.set(vector, 0);

	apr::Quaternion conjugateQuaternion;
	conjugateQuaternion.set(quat);
	conjugateQuaternion.conjugate();

	apr::Quaternion resultQuaternion = quat * vectorQuaternion * conjugateQuaternion;

	return resultQuaternion.axis();
}
