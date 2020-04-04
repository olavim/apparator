#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "stb_image.h"

#include "texture.hpp"

namespace apr = apparator;

apr::Texture::Texture(std::string filePath) {
	glGenTextures(1, &this->id);

	int nrChannels;
	unsigned char *data = stbi_load(filePath.c_str(), &this->width, &this->height, &nrChannels, 0);

	if (data) {
		int format;
		if (nrChannels == 1) {
			format = GL_RED;
		} else if (nrChannels == 3) {
			format = GL_RGB;
		} else if (nrChannels == 4) {
			format = GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, this->id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

apr::Texture::~Texture() {
	glDeleteTextures(1, &this->id);
}

void apr::Texture::bind() const {
	glBindTexture(GL_TEXTURE_2D, this->id);
}
