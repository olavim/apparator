#include <GL/glew.h>
#include <math.h>

#include "math.hpp"

using namespace apparator;

math::mat4::mat4() {
	this->arr[0] = math::vec4();
	this->arr[1] = math::vec4();
	this->arr[2] = math::vec4();
	this->arr[3] = math::vec4();
}

math::mat4::mat4(const GLfloat identity) {
	this->arr[0] = math::vec4(identity, 0, 0, 0);
	this->arr[1] = math::vec4(0, identity, 0, 0);
	this->arr[2] = math::vec4(0, 0, identity, 0);
	this->arr[3] = math::vec4(0, 0, 0, identity);
}

math::mat4::mat4(const math::vec4 &row1, const math::vec4 &row2, const math::vec4 &row3, const math::vec4 &row4) {
	this->arr[0] = row1;
	this->arr[1] = row2;
	this->arr[2] = row3;
	this->arr[3] = row4;
}

math::vec4 &math::mat4::operator [] (const int index) {
	return this->arr[index];
}

const math::vec4 &math::mat4::operator [] (const int index) const {
	return this->arr[index];
}

math::mat4 &math::mat4::operator *= (const mat4& matrix) {
	math::vec4 newCol1 = matrix * math::vec4((*this)[0][0], (*this)[1][0], (*this)[2][0], (*this)[3][0]);
	math::vec4 newCol2 = matrix * math::vec4((*this)[0][1], (*this)[1][1], (*this)[2][1], (*this)[3][1]);
	math::vec4 newCol3 = matrix * math::vec4((*this)[0][2], (*this)[1][2], (*this)[2][2], (*this)[3][2]);
	math::vec4 newCol4 = matrix * math::vec4((*this)[0][3], (*this)[1][3], (*this)[2][3], (*this)[3][3]);

	this->arr[0] = math::vec4(newCol1[0], newCol2[0], newCol3[0], newCol4[0]);
	this->arr[1] = math::vec4(newCol1[1], newCol2[1], newCol3[1], newCol4[1]);
	this->arr[2] = math::vec4(newCol1[2], newCol2[2], newCol3[2], newCol4[2]);
	this->arr[3] = math::vec4(newCol1[3], newCol2[3], newCol3[3], newCol4[3]);
	return *this;
}

math::mat4 &math::mat4::operator - () {
	(*this) *= -1;
	return *this;
}

math::vec4 math::operator * (math::mat4 lhs, const vec4& columnVector) {
	return math::vec4(
		lhs[0] * columnVector,
		lhs[1] * columnVector,
		lhs[2] * columnVector,
		lhs[3] * columnVector
	);
}

math::mat4 math::operator * (math::mat4 lhs, const mat4& rhs) {
	lhs *= rhs;
	return lhs;
}
