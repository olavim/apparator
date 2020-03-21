#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "stb_image.h"

#include "texture.hpp"

namespace apr = apparator;

apr::Texture::Texture(std::string filePath) {
	glGenTextures(1, &this->id);
	glBindTexture(GL_TEXTURE_2D, this->id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int nrChannels;
	unsigned char *data = stbi_load(filePath.c_str(), &this->width, &this->height, &nrChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
}

apr::Texture::~Texture() {
	glDeleteTextures(1, &this->id);
}

void apr::Texture::bind() const {
	glBindTexture(GL_TEXTURE_2D, this->id);
}
