#pragma once

#ifndef M_PI
	#define M_PI 3.141592653589793238462643383279502884L
#endif

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace apparator {
	namespace math {
		class vec3 {
				GLfloat arr[3];
			public:
				vec3();
				vec3(GLfloat a, GLfloat b, GLfloat c);
				vec3(const vec3 &vector);

				GLfloat magnitude();
				const GLfloat magnitude() const;

				GLfloat& operator [] (const int index);
				const GLfloat& operator [] (const int index) const;

				vec3 &operator *= (GLfloat scalar);
				vec3 &operator += (const vec3 &vector);
				vec3 &operator -= (const vec3 &vector);
		};

		vec3 operator * (vec3 lhs, GLfloat scalar);
		GLfloat operator * (vec3 lhsRow, const vec3 &rhsColumn);
		vec3 operator + (vec3 lhs, const vec3 &rhs);
		vec3 operator - (vec3 lhs, const vec3 &rhs);

		class vec4 {
				GLfloat arr[4];
			public:
				vec4();
				vec4(GLfloat a, GLfloat b, GLfloat c, GLfloat d);
				vec4(const vec4 &vector);
				vec4(const vec3 &vector, GLfloat d);
				vec4(GLfloat d, const vec3 &vector);

				GLfloat magnitude();
				const GLfloat magnitude() const;

				GLfloat& operator [] (int index);
				const GLfloat& operator [] (int index) const;

				vec4 &operator *= (GLfloat scalar);
				vec4 &operator += (const vec4 &vector);
				vec4 &operator -= (const vec4 &vector);
		};

		vec4 operator * (vec4 lhs, GLfloat scalar);
		GLfloat operator * (vec4 lhs, const vec4 &column);
		vec4 operator + (vec4 lhs, const vec4 &vector);
		vec4 operator - (vec4 lhs, const vec4 &vector);

		class mat4 {
				vec4 arr[4];
			public:
				mat4();
				mat4(const GLfloat identity);
				mat4(const vec4 &row1, const vec4 &row2, const vec4 &row3, const vec4 &row4);

				vec4 &operator [] (const int index);
				const vec4 &operator [] (const int index) const;

				mat4 &operator *= (const mat4 &matrix);
		};

		vec4 operator * (mat4 lhs, const vec4 &columnVector);
		mat4 operator * (mat4 lhs, const mat4 &rhs);

		GLfloat radians(const GLfloat angle);

		mat4 perspective(const GLfloat fov, const GLfloat aspect, const GLfloat near, const GLfloat far);
		mat4 lookAt(const vec3 &eye, const vec3 &target, const vec3 &up);

		GLfloat dot(const vec3 &a, const vec3 &b);
		vec3 cross(const vec3 &a, const vec3 &b);
		vec3 normalize(const vec3 &a);
		vec4 normalize(const vec4 &a);

		void printVec(const math::vec3 &vec);
		void printVec(const math::vec4 &vec);
		void printMat(const math::mat4 &mat);
	}
}
