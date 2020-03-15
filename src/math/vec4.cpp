#include <GL/glew.h>
#include <math.h>

#include "math.hpp"

using namespace apparator;

math::vec4::vec4() {
	this->arr[0] = 0;
	this->arr[1] = 0;
	this->arr[2] = 0;
	this->arr[3] = 0;
}

math::vec4::vec4(GLfloat a, GLfloat b, GLfloat c, GLfloat d) {
	this->arr[0] = a;
	this->arr[1] = b;
	this->arr[2] = c;
	this->arr[3] = d;
}

math::vec4::vec4(const math::vec4 &vector) {
	this->arr[0] = vector[0];
	this->arr[1] = vector[1];
	this->arr[2] = vector[2];
	this->arr[3] = vector[3];
}

math::vec4::vec4(const math::vec3 &vector, GLfloat d) {
	this->arr[0] = vector[0];
	this->arr[1] = vector[1];
	this->arr[2] = vector[2];
	this->arr[3] = d;
}

math::vec4::vec4(GLfloat d, const math::vec3 &vector) {
	this->arr[0] = d;
	this->arr[1] = vector[0];
	this->arr[2] = vector[1];
	this->arr[3] = vector[2];
}

GLfloat math::vec4::magnitude() {
	GLfloat *a = this->arr;
	return sqrt((a[0] * a[0]) + (a[1] * a[1]) + (a[2] * a[2]) + (a[3] * a[3]));
}

GLfloat math::vec4::magnitude() const {
	const GLfloat *a = this->arr;
	return sqrt((a[0] * a[0]) + (a[1] * a[1]) + (a[2] * a[2]) + (a[3] * a[3]));
}

GLfloat &math::vec4::operator [] (const int index) {
	return this->arr[index];
}

const GLfloat &math::vec4::operator [] (const int index) const {
	return this->arr[index];
}

math::vec4 &math::vec4::operator *= (GLfloat scalar) {
	this->arr[0] *= scalar;
	this->arr[1] *= scalar;
	this->arr[2] *= scalar;
	this->arr[3] *= scalar;
	return *this;
}

math::vec4 &math::vec4::operator += (const math::vec4 &vector) {
	this->arr[0] += vector[0];
	this->arr[1] += vector[1];
	this->arr[2] += vector[2];
	this->arr[3] += vector[3];
	return *this;
}

math::vec4 &math::vec4::operator -= (const math::vec4 &vector) {
	this->arr[0] -= vector[0];
	this->arr[1] -= vector[1];
	this->arr[2] -= vector[2];
	this->arr[3] -= vector[3];
	return *this;
}

math::vec4 math::operator * (math::vec4 lhs, GLfloat scalar) {
	lhs *= scalar;
	return lhs;
}

GLfloat math::operator * (math::vec4 lhsRow, const math::vec4 &rhsColumn) {
	return (lhsRow[0] * rhsColumn[0]) + (lhsRow[1] * rhsColumn[1]) + (lhsRow[2] * rhsColumn[2]) + (lhsRow[3] * rhsColumn[3]);
}

math::vec4 math::operator + (math::vec4 lhs, const math::vec4 &rhs) {
	lhs += rhs;
	return lhs;
}

math::vec4 math::operator - (math::vec4 lhs, const math::vec4 &rhs) {
	lhs -= rhs;
	return lhs;
}
