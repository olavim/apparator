#include <GL/glew.h>
#include <math.h>

#include "math.hpp"

namespace apr = apparator;

apr::mat4::mat4() {
	this->arr[0] = vec4();
	this->arr[1] = vec4();
	this->arr[2] = vec4();
	this->arr[3] = vec4();
}

apr::mat4::mat4(const GLfloat identity) {
	this->arr[0] = vec4(identity, 0, 0, 0);
	this->arr[1] = vec4(0, identity, 0, 0);
	this->arr[2] = vec4(0, 0, identity, 0);
	this->arr[3] = vec4(0, 0, 0, identity);
}

apr::mat4::mat4(const vec4 &row1, const vec4 &row2, const vec4 &row3, const vec4 &row4) {
	this->arr[0] = row1;
	this->arr[1] = row2;
	this->arr[2] = row3;
	this->arr[3] = row4;
}

apr::vec4 &apr::mat4::operator [] (const int index) {
	return this->arr[index];
}

const apr::vec4 &apr::mat4::operator [] (const int index) const {
	return this->arr[index];
}

apr::mat4 &apr::mat4::operator *= (const apr::mat4& matrix) {
	apr::vec4 newCol1 = matrix * vec4((*this)[0][0], (*this)[1][0], (*this)[2][0], (*this)[3][0]);
	apr::vec4 newCol2 = matrix * vec4((*this)[0][1], (*this)[1][1], (*this)[2][1], (*this)[3][1]);
	apr::vec4 newCol3 = matrix * vec4((*this)[0][2], (*this)[1][2], (*this)[2][2], (*this)[3][2]);
	apr::vec4 newCol4 = matrix * vec4((*this)[0][3], (*this)[1][3], (*this)[2][3], (*this)[3][3]);

	this->arr[0] = apr::vec4(newCol1[0], newCol2[0], newCol3[0], newCol4[0]);
	this->arr[1] = apr::vec4(newCol1[1], newCol2[1], newCol3[1], newCol4[1]);
	this->arr[2] = apr::vec4(newCol1[2], newCol2[2], newCol3[2], newCol4[2]);
	this->arr[3] = apr::vec4(newCol1[3], newCol2[3], newCol3[3], newCol4[3]);
	return *this;
}

apr::mat4 &apr::mat4::operator - () {
	(*this) *= -1;
	return *this;
}

apr::vec4 apr::operator * (apr::mat4 lhs, const apr::vec4& columnVector) {
	return apr::vec4(
		lhs[0] * columnVector,
		lhs[1] * columnVector,
		lhs[2] * columnVector,
		lhs[3] * columnVector
	);
}

apr::mat4 apr::operator * (apr::mat4 lhs, const apr::mat4& rhs) {
	lhs *= rhs;
	return lhs;
}
