#pragma once

#include "math.hpp"

namespace apparator {
	class Transform {
		public:
			void translate(float x, float y, float z);
			void scale(float x, float y, float z);
			void setScale(float x, float y, float z);
			void rotate(float x, float y, float z);
			void setRotation(float x, float y, float z);
			mat4 matrix();
			const vec3& translation();
			const vec3& scale();
			const vec3& rotation();
			vec3 forward();
			vec3 right();
			vec3 up();
		private:
			vec3 _translation = vec3();
			vec3 _scale = vec3(1, 1, 1);
			vec3 _rotation = vec3();
	};
}
