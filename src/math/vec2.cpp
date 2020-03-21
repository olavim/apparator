#include <GL/glew.h>
#include <math.h>

#include "math.hpp"

namespace apr = apparator;

apr::vec2::vec2() {
	this->arr[0] = 0;
	this->arr[1] = 0;
	this->arr[2] = 0;
}

apr::vec2::vec2(GLfloat a, GLfloat b) {
	this->arr[0] = a;
	this->arr[1] = b;
}

apr::vec2::vec2(const apr::vec2 &vector) {
	this->arr[0] = vector[0];
	this->arr[1] = vector[1];
}

GLfloat apr::vec2::magnitude() {
	GLfloat *a = this->arr;
	return sqrt((a[0] * a[0]) + (a[1] * a[1]));
}

GLfloat apr::vec2::magnitude() const {
	const GLfloat *a = this->arr;
	return sqrt((a[0] * a[0]) + (a[1] * a[1]));
}

GLfloat &apr::vec2::operator [] (const int index) {
	return this->arr[index];
}

const GLfloat &apr::vec2::operator [] (const int index) const {
	return this->arr[index];
}

apr::vec2 &apr::vec2::operator *= (GLfloat scalar) {
	this->arr[0] *= scalar;
	this->arr[1] *= scalar;
	return *this;
}

apr::vec2 &apr::vec2::operator += (const apr::vec2 &vector) {
	this->arr[0] += vector[0];
	this->arr[1] += vector[1];
	return *this;
}

apr::vec2 &apr::vec2::operator -= (const apr::vec2 &vector) {
	this->arr[0] -= vector[0];
	this->arr[1] -= vector[1];
	return *this;
}

apr::vec2 &apr::vec2::operator - () {
	(*this) *= -1;
	return *this;
}

apr::vec2 apr::operator * (apr::vec2 lhs, GLfloat scalar) {
	lhs *= scalar;
	return lhs;
}

GLfloat apr::operator * (apr::vec2 lhsRow, const apr::vec2 &rhsColumn) {
	return (lhsRow[0] * rhsColumn[0]) + (lhsRow[1] * rhsColumn[1]);
}

apr::vec2 apr::operator + (apr::vec2 lhs, const apr::vec2 &rhs) {
	lhs += rhs;
	return lhs;
}

apr::vec2 apr::operator - (apr::vec2 lhs, const apr::vec2 &rhs) {
	lhs -= rhs;
	return lhs;
}
