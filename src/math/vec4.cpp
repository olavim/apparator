#include <GL/glew.h>
#include <math.h>

#include "math.hpp"

namespace apr = apparator;

apr::vec4::vec4() {
	this->arr[0] = 0;
	this->arr[1] = 0;
	this->arr[2] = 0;
	this->arr[3] = 0;
}

apr::vec4::vec4(GLfloat a, GLfloat b, GLfloat c, GLfloat d) {
	this->arr[0] = a;
	this->arr[1] = b;
	this->arr[2] = c;
	this->arr[3] = d;
}

apr::vec4::vec4(const apr::vec4 &vector) {
	this->arr[0] = vector[0];
	this->arr[1] = vector[1];
	this->arr[2] = vector[2];
	this->arr[3] = vector[3];
}

apr::vec4::vec4(const vec3 &vector, GLfloat d) {
	this->arr[0] = vector[0];
	this->arr[1] = vector[1];
	this->arr[2] = vector[2];
	this->arr[3] = d;
}

apr::vec4::vec4(GLfloat d, const vec3 &vector) {
	this->arr[0] = d;
	this->arr[1] = vector[0];
	this->arr[2] = vector[1];
	this->arr[3] = vector[2];
}

GLfloat apr::vec4::magnitude() {
	GLfloat *a = this->arr;
	return sqrt((a[0] * a[0]) + (a[1] * a[1]) + (a[2] * a[2]) + (a[3] * a[3]));
}

GLfloat apr::vec4::magnitude() const {
	const GLfloat *a = this->arr;
	return sqrt((a[0] * a[0]) + (a[1] * a[1]) + (a[2] * a[2]) + (a[3] * a[3]));
}

GLfloat &apr::vec4::operator [] (const int index) {
	return this->arr[index];
}

const GLfloat &apr::vec4::operator [] (const int index) const {
	return this->arr[index];
}

apr::vec4 &apr::vec4::operator *= (GLfloat scalar) {
	this->arr[0] *= scalar;
	this->arr[1] *= scalar;
	this->arr[2] *= scalar;
	this->arr[3] *= scalar;
	return *this;
}

apr::vec4 &apr::vec4::operator += (const apr::vec4 &vector) {
	this->arr[0] += vector[0];
	this->arr[1] += vector[1];
	this->arr[2] += vector[2];
	this->arr[3] += vector[3];
	return *this;
}

apr::vec4 &apr::vec4::operator -= (const apr::vec4 &vector) {
	this->arr[0] -= vector[0];
	this->arr[1] -= vector[1];
	this->arr[2] -= vector[2];
	this->arr[3] -= vector[3];
	return *this;
}

apr::vec4 &apr::vec4::operator - () {
	(*this) *= -1;
	return *this;
}

apr::vec4 apr::operator * (apr::vec4 lhs, GLfloat scalar) {
	lhs *= scalar;
	return lhs;
}

GLfloat apr::operator * (apr::vec4 lhsRow, const apr::vec4 &rhsColumn) {
	return (lhsRow[0] * rhsColumn[0]) + (lhsRow[1] * rhsColumn[1]) + (lhsRow[2] * rhsColumn[2]) + (lhsRow[3] * rhsColumn[3]);
}

apr::vec4 apr::operator + (apr::vec4 lhs, const apr::vec4 &rhs) {
	lhs += rhs;
	return lhs;
}

apr::vec4 apr::operator - (apr::vec4 lhs, const apr::vec4 &rhs) {
	lhs -= rhs;
	return lhs;
}
