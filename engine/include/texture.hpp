#pragma once

#include <string>
#include "math.hpp"

namespace apparator {
	class Texture {
		public:
			unsigned int id;

			Texture() : id(0) {};
			Texture(std::string filePath);
			~Texture();

			void bind() const;
		private:
			int width;
			int height;
	};
}
