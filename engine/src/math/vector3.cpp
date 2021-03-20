#include <GL/glew.h>
#include <math.h>

#include "vector3.hpp"

namespace apr = apparator;

float apr::Vector3::magnitude() {
	float *a = this->arr;
	return sqrtf((a[0] * a[0]) + (a[1] * a[1]) + (a[2] * a[2]));
}

float apr::Vector3::magnitude() const {
	const float *a = this->arr;
	return sqrtf((a[0] * a[0]) + (a[1] * a[1]) + (a[2] * a[2]));
}

float &apr::Vector3::operator [] (const int index) {
	return this->arr[index];
}

const float &apr::Vector3::operator [] (const int index) const {
	return this->arr[index];
}

apr::Vector3 &apr::Vector3::operator *= (float scalar) {
	this->arr[0] *= scalar;
	this->arr[1] *= scalar;
	this->arr[2] *= scalar;
	return *this;
}

apr::Vector3 &apr::Vector3::operator += (const apr::Vector3 &vector) {
	this->arr[0] += vector[0];
	this->arr[1] += vector[1];
	this->arr[2] += vector[2];
	return *this;
}

apr::Vector3 &apr::Vector3::operator -= (const apr::Vector3 &vector) {
	this->arr[0] -= vector[0];
	this->arr[1] -= vector[1];
	this->arr[2] -= vector[2];
	return *this;
}

apr::Vector3 &apr::Vector3::operator - () {
	(*this) *= -1;
	return *this;
}

apr::Vector3 apr::operator * (apr::Vector3 lhs, float scalar) {
	lhs *= scalar;
	return lhs;
}

float apr::operator * (apr::Vector3 lhsRow, const apr::Vector3 &rhsColumn) {
	return (lhsRow[0] * rhsColumn[0]) + (lhsRow[1] * rhsColumn[1]) + (lhsRow[2] * rhsColumn[2]);
}

apr::Vector3 apr::operator + (apr::Vector3 lhs, const apr::Vector3 &rhs) {
	lhs += rhs;
	return lhs;
}

apr::Vector3 apr::operator - (apr::Vector3 lhs, const apr::Vector3 &rhs) {
	lhs -= rhs;
	return lhs;
}
