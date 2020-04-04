#include <GL/glew.h>
#include <math.h>

#include "math.hpp"

namespace apr = apparator;

apr::Vector2::Vector2() {
	this->arr[0] = 0;
	this->arr[1] = 0;
	this->arr[2] = 0;
}

apr::Vector2::Vector2(float a, float b) {
	this->arr[0] = a;
	this->arr[1] = b;
}

apr::Vector2::Vector2(const apr::Vector2 &vector) {
	this->arr[0] = vector[0];
	this->arr[1] = vector[1];
}

float apr::Vector2::magnitude() {
	float *a = this->arr;
	return sqrt((a[0] * a[0]) + (a[1] * a[1]));
}

float apr::Vector2::magnitude() const {
	const float *a = this->arr;
	return sqrt((a[0] * a[0]) + (a[1] * a[1]));
}

float &apr::Vector2::operator [] (const int index) {
	return this->arr[index];
}

const float &apr::Vector2::operator [] (const int index) const {
	return this->arr[index];
}

apr::Vector2 &apr::Vector2::operator *= (float scalar) {
	this->arr[0] *= scalar;
	this->arr[1] *= scalar;
	return *this;
}

apr::Vector2 &apr::Vector2::operator += (const apr::Vector2 &vector) {
	this->arr[0] += vector[0];
	this->arr[1] += vector[1];
	return *this;
}

apr::Vector2 &apr::Vector2::operator -= (const apr::Vector2 &vector) {
	this->arr[0] -= vector[0];
	this->arr[1] -= vector[1];
	return *this;
}

apr::Vector2 &apr::Vector2::operator - () {
	(*this) *= -1;
	return *this;
}

apr::Vector2 apr::operator * (apr::Vector2 lhs, float scalar) {
	lhs *= scalar;
	return lhs;
}

float apr::operator * (apr::Vector2 lhsRow, const apr::Vector2 &rhsColumn) {
	return (lhsRow[0] * rhsColumn[0]) + (lhsRow[1] * rhsColumn[1]);
}

apr::Vector2 apr::operator + (apr::Vector2 lhs, const apr::Vector2 &rhs) {
	lhs += rhs;
	return lhs;
}

apr::Vector2 apr::operator - (apr::Vector2 lhs, const apr::Vector2 &rhs) {
	lhs -= rhs;
	return lhs;
}
