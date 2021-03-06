#pragma once

#include <string>

namespace apparator {
	class Texture {
		public:
			unsigned int id;

			Texture() : id(0), width(0), height(0) {};
			Texture(std::string filePath);
			~Texture();

			void bind() const;
		private:
			int width;
			int height;
	};
}
