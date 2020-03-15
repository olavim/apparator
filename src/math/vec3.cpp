#include <GL/glew.h>
#include <math.h>

#include "math.hpp"

using namespace apparator;

math::vec3::vec3() {
	this->arr[0] = 0;
	this->arr[1] = 0;
	this->arr[2] = 0;
}

math::vec3::vec3(GLfloat a, GLfloat b, GLfloat c) {
	this->arr[0] = a;
	this->arr[1] = b;
	this->arr[2] = c;
}

math::vec3::vec3(const math::vec3 &vector) {
	this->arr[0] = vector[0];
	this->arr[1] = vector[1];
	this->arr[2] = vector[2];
}

GLfloat math::vec3::magnitude() {
	GLfloat *arr = this->arr;
	return sqrt((arr[0] * arr[0]) + (arr[1] * arr[1]) + (arr[2] * arr[2]));
}

const GLfloat math::vec3::magnitude() const {
	const GLfloat *arr = this->arr;
	return sqrt((arr[0] * arr[0]) + (arr[1] * arr[1]) + (arr[2] * arr[2]));
}

GLfloat &math::vec3::operator [] (const int index) {
	return this->arr[index];
}

const GLfloat &math::vec3::operator [] (const int index) const {
	return this->arr[index];
}

math::vec3 &math::vec3::operator *= (GLfloat scalar) {
	this->arr[0] *= scalar;
	this->arr[1] *= scalar;
	this->arr[2] *= scalar;
	return *this;
}

math::vec3 &math::vec3::operator += (const math::vec3 &vector) {
	this->arr[0] += vector[0];
	this->arr[1] += vector[1];
	this->arr[2] += vector[2];
	return *this;
}

math::vec3 &math::vec3::operator -= (const math::vec3 &vector) {
	this->arr[0] -= vector[0];
	this->arr[1] -= vector[1];
	this->arr[2] -= vector[2];
	return *this;
}

math::vec3 math::operator * (math::vec3 lhs, GLfloat scalar) {
	lhs *= scalar;
	return lhs;
}

GLfloat math::operator * (math::vec3 lhsRow, const math::vec3 &rhsColumn) {
	return (lhsRow[0] * rhsColumn[0]) + (lhsRow[1] * rhsColumn[1]) + (lhsRow[2] * rhsColumn[2]);
}

math::vec3 math::operator + (math::vec3 lhs, const math::vec3 &rhs) {
	lhs += rhs;
	return lhs;
}

math::vec3 math::operator - (math::vec3 lhs, const math::vec3 &rhs) {
	lhs -= rhs;
	return lhs;
}
