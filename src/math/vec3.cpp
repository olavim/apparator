#include <GL/glew.h>
#include <math.h>

#include "math.hpp"

namespace apr = apparator;

apr::vec3::vec3() {
	this->arr[0] = 0;
	this->arr[1] = 0;
	this->arr[2] = 0;
}

apr::vec3::vec3(GLfloat a, GLfloat b, GLfloat c) {
	this->arr[0] = a;
	this->arr[1] = b;
	this->arr[2] = c;
}

apr::vec3::vec3(const apr::vec3 &vector) {
	this->arr[0] = vector[0];
	this->arr[1] = vector[1];
	this->arr[2] = vector[2];
}

GLfloat apr::vec3::magnitude() {
	GLfloat *a = this->arr;
	return sqrt((a[0] * a[0]) + (a[1] * a[1]) + (a[2] * a[2]));
}

GLfloat apr::vec3::magnitude() const {
	const GLfloat *a = this->arr;
	return sqrt((a[0] * a[0]) + (a[1] * a[1]) + (a[2] * a[2]));
}

GLfloat &apr::vec3::operator [] (const int index) {
	return this->arr[index];
}

const GLfloat &apr::vec3::operator [] (const int index) const {
	return this->arr[index];
}

apr::vec3 &apr::vec3::operator *= (GLfloat scalar) {
	this->arr[0] *= scalar;
	this->arr[1] *= scalar;
	this->arr[2] *= scalar;
	return *this;
}

apr::vec3 &apr::vec3::operator += (const apr::vec3 &vector) {
	this->arr[0] += vector[0];
	this->arr[1] += vector[1];
	this->arr[2] += vector[2];
	return *this;
}

apr::vec3 &apr::vec3::operator -= (const apr::vec3 &vector) {
	this->arr[0] -= vector[0];
	this->arr[1] -= vector[1];
	this->arr[2] -= vector[2];
	return *this;
}

apr::vec3 &apr::vec3::operator - () {
	(*this) *= -1;
	return *this;
}

apr::vec3 apr::operator * (apr::vec3 lhs, GLfloat scalar) {
	lhs *= scalar;
	return lhs;
}

GLfloat apr::operator * (apr::vec3 lhsRow, const apr::vec3 &rhsColumn) {
	return (lhsRow[0] * rhsColumn[0]) + (lhsRow[1] * rhsColumn[1]) + (lhsRow[2] * rhsColumn[2]);
}

apr::vec3 apr::operator + (apr::vec3 lhs, const apr::vec3 &rhs) {
	lhs += rhs;
	return lhs;
}

apr::vec3 apr::operator - (apr::vec3 lhs, const apr::vec3 &rhs) {
	lhs -= rhs;
	return lhs;
}
