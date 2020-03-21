#include <fstream>
#include <sstream>
#include <string>

#include "math.hpp"
#include "texture.hpp"
#include "material.hpp"
#include "model.hpp"

namespace apr = apparator;

void apr::Model::addTexture(const Texture* texture) {
	this->textures.push_back(texture);
}

void apr::Model::addMaterial(const Material* material) {
	this->materials.push_back(material);
}

void apr::Model::draw() {
	this->mesh.bind();

	unsigned int vertexOffset = 0;

	for (unsigned int i = 0; i < this->mesh.numParts(); i++) {
		this->textures[i]->bind();
		this->materials[i]->bind();

		unsigned int vertexCount = this->mesh.getPart(i).vertexCount;
		glDrawArrays(GL_TRIANGLES, vertexOffset, vertexCount);
		vertexOffset += vertexCount;
	}
}
