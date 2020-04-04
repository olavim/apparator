#include <GL/glew.h>
#include <math.h>

#include "math.hpp"

namespace apr = apparator;

apr::Vector4::Vector4() {
	this->arr[0] = 0;
	this->arr[1] = 0;
	this->arr[2] = 0;
	this->arr[3] = 0;
}

apr::Vector4::Vector4(float a, float b, float c, float d) {
	this->arr[0] = a;
	this->arr[1] = b;
	this->arr[2] = c;
	this->arr[3] = d;
}

apr::Vector4::Vector4(const apr::Vector4 &vector) {
	this->arr[0] = vector[0];
	this->arr[1] = vector[1];
	this->arr[2] = vector[2];
	this->arr[3] = vector[3];
}

apr::Vector4::Vector4(const apr::Vector3 &vector, float d) {
	this->arr[0] = vector[0];
	this->arr[1] = vector[1];
	this->arr[2] = vector[2];
	this->arr[3] = d;
}

apr::Vector4::Vector4(float d, const apr::Vector3 &vector) {
	this->arr[0] = d;
	this->arr[1] = vector[0];
	this->arr[2] = vector[1];
	this->arr[3] = vector[2];
}

float apr::Vector4::magnitude() {
	float *a = this->arr;
	return sqrtf((a[0] * a[0]) + (a[1] * a[1]) + (a[2] * a[2]) + (a[3] * a[3]));
}

float apr::Vector4::magnitude() const {
	const float *a = this->arr;
	return sqrtf((a[0] * a[0]) + (a[1] * a[1]) + (a[2] * a[2]) + (a[3] * a[3]));
}

float &apr::Vector4::operator [] (const int index) {
	return this->arr[index];
}

const float &apr::Vector4::operator [] (const int index) const {
	return this->arr[index];
}

apr::Vector4 &apr::Vector4::operator *= (float scalar) {
	this->arr[0] *= scalar;
	this->arr[1] *= scalar;
	this->arr[2] *= scalar;
	this->arr[3] *= scalar;
	return *this;
}

apr::Vector4 &apr::Vector4::operator += (const apr::Vector4 &vector) {
	this->arr[0] += vector[0];
	this->arr[1] += vector[1];
	this->arr[2] += vector[2];
	this->arr[3] += vector[3];
	return *this;
}

apr::Vector4 &apr::Vector4::operator -= (const apr::Vector4 &vector) {
	this->arr[0] -= vector[0];
	this->arr[1] -= vector[1];
	this->arr[2] -= vector[2];
	this->arr[3] -= vector[3];
	return *this;
}

apr::Vector4 &apr::Vector4::operator - () {
	(*this) *= -1;
	return *this;
}

apr::Vector4 apr::operator * (apr::Vector4 lhs, float scalar) {
	lhs *= scalar;
	return lhs;
}

float apr::operator * (apr::Vector4 lhsRow, const apr::Vector4 &rhsColumn) {
	return (lhsRow[0] * rhsColumn[0]) + (lhsRow[1] * rhsColumn[1]) + (lhsRow[2] * rhsColumn[2]) + (lhsRow[3] * rhsColumn[3]);
}

apr::Vector4 apr::operator + (apr::Vector4 lhs, const apr::Vector4 &rhs) {
	lhs += rhs;
	return lhs;
}

apr::Vector4 apr::operator - (apr::Vector4 lhs, const apr::Vector4 &rhs) {
	lhs -= rhs;
	return lhs;
}
