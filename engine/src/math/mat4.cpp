#include <GL/glew.h>
#include <math.h>
#include <cstring>

#include "mat4.hpp"

namespace apr = apparator;

apr::Matrix4::Matrix4() {
	this->set(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
}

apr::Matrix4::Matrix4(const Matrix4& matrix) {
	memcpy(m, matrix.m, 16 * sizeof(float));
}

apr::Matrix4::Matrix4(const float identity) {
	this->set(
		identity, 0, 0, 0,
		0, identity, 0, 0,
		0, 0, identity, 0,
		0, 0, 0, identity
	);
}

apr::Matrix4::Matrix4(
	float e00, float e01, float e02, float e03, float e10, float e11, float e12, float e13,
	float e20, float e21, float e22, float e23, float e30, float e31, float e32, float e33
) {
	this->set(e00, e01, e02, e03, e10, e11, e12, e13, e20, e21, e22, e23, e30, e31, e32, e33);
}

void apr::Matrix4::set(
	float e00, float e01, float e02, float e03, float e10, float e11, float e12, float e13,
	float e20, float e21, float e22, float e23, float e30, float e31, float e32, float e33
) {
	this->m[0] = e00;
	this->m[1] = e10;
	this->m[2] = e20;
	this->m[3] = e30;
	this->m[4] = e01;
	this->m[5] = e11;
	this->m[6] = e21;
	this->m[7] = e31;
	this->m[8] = e02;
	this->m[9] = e12;
	this->m[10] = e22;
	this->m[11] = e32;
	this->m[12] = e03;
	this->m[13] = e13;
	this->m[14] = e23;
	this->m[15] = e33;
}

bool apr::Matrix4::invert() {
	float a0 = m[0] * m[5] - m[1] * m[4];
	float a1 = m[0] * m[6] - m[2] * m[4];
	float a2 = m[0] * m[7] - m[3] * m[4];
	float a3 = m[1] * m[6] - m[2] * m[5];
	float a4 = m[1] * m[7] - m[3] * m[5];
	float a5 = m[2] * m[7] - m[3] * m[6];
	float b0 = m[8] * m[13] - m[9] * m[12];
	float b1 = m[8] * m[14] - m[10] * m[12];
	float b2 = m[8] * m[15] - m[11] * m[12];
	float b3 = m[9] * m[14] - m[10] * m[13];
	float b4 = m[9] * m[15] - m[11] * m[13];
	float b5 = m[10] * m[15] - m[11] * m[14];

	float det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;

	if (fabs(det) <= 2e-30) {
		return false;
	}

	this->set(
		m[5] * b5 - m[6] * b4 + m[7] * b3,
		-m[4] * b5 + m[6] * b2 - m[7] * b1,
		m[4] * b4 - m[5] * b2 + m[7] * b0,
		-m[4] * b3 + m[5] * b1 - m[6] * b0,

		-m[1] * b5 + m[2] * b4 - m[3] * b3,
		m[0] * b5 - m[2] * b2 + m[3] * b1,
		-m[0] * b4 + m[1] * b2 - m[3] * b0,
		m[0] * b3 - m[1] * b1 + m[2] * b0,

		m[13] * a5 - m[14] * a4 + m[15] * a3,
		-m[12] * a5 + m[14] * a2 - m[15] * a1,
		m[12] * a4 - m[13] * a2 + m[15] * a0,
		-m[12] * a3 + m[13] * a1 - m[14] * a0,

		-m[9] * a5 + m[10] * a4 - m[11] * a3,
		m[8] * a5 - m[10] * a2 + m[11] * a1,
		-m[8] * a4 + m[9] * a2 - m[11] * a0,
		m[8] * a3 - m[9] * a1 + m[10] * a0
	);

	*this *= det;

	return true;
}

void apr::Matrix4::transpose() {
	this->set(
		m[0], m[1], m[2], m[3],
		m[4], m[5], m[6], m[7],
		m[8], m[9], m[10], m[11],
		m[12], m[13], m[14], m[15]
	);
}

apr::Matrix4 &apr::Matrix4::operator *= (const apr::Matrix4& matrix) {
	const float *m2 = matrix.m;

	float product[16];

	product[0] = m[0] * m2[0] + m[4] * m2[1] + m[8] * m2[2] + m[12] * m2[3];
	product[1] = m[1] * m2[0] + m[5] * m2[1] + m[9] * m2[2] + m[13] * m2[3];
	product[2] = m[2] * m2[0] + m[6] * m2[1] + m[10] * m2[2] + m[14] * m2[3];
	product[3] = m[3] * m2[0] + m[7] * m2[1] + m[11] * m2[2] + m[15] * m2[3];

	product[4] = m[0] * m2[4] + m[4] * m2[5] + m[8] * m2[6] + m[12] * m2[7];
	product[5] = m[1] * m2[4] + m[5] * m2[5] + m[9] * m2[6] + m[13] * m2[7];
	product[6] = m[2] * m2[4] + m[6] * m2[5] + m[10] * m2[6] + m[14] * m2[7];
	product[7] = m[3] * m2[4] + m[7] * m2[5] + m[11] * m2[6] + m[15] * m2[7];

	product[8] = m[0] * m2[8] + m[4] * m2[9] + m[8] * m2[10] + m[12] * m2[11];
	product[9] = m[1] * m2[8] + m[5] * m2[9] + m[9] * m2[10] + m[13] * m2[11];
	product[10] = m[2] * m2[8] + m[6] * m2[9] + m[10] * m2[10] + m[14] * m2[11];
	product[11] = m[3] * m2[8] + m[7] * m2[9] + m[11] * m2[10] + m[15] * m2[11];

	product[12] = m[0] * m2[12] + m[4] * m2[13] + m[8] * m2[14] + m[12] * m2[15];
	product[13] = m[1] * m2[12] + m[5] * m2[13] + m[9] * m2[14] + m[13] * m2[15];
	product[14] = m[2] * m2[12] + m[6] * m2[13] + m[10] * m2[14] + m[14] * m2[15];
	product[15] = m[3] * m2[12] + m[7] * m2[13] + m[11] * m2[14] + m[15] * m2[15];

	memcpy(m, product, 16 * sizeof(float));

	return *this;
}

apr::Matrix4 &apr::Matrix4::operator - () {
	(*this) *= -1;
	return *this;
}

apr::Matrix4 apr::operator * (apr::Matrix4 lhs, const apr::Matrix4& rhs) {
	lhs *= rhs;
	return lhs;
}
