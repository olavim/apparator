#include <vector>
#include <iostream>
#include <GL/glew.h>

#include "mesh.hpp"

namespace apr = apparator;

apr::Mesh::Mesh(const apr::VertexLayout& lt, const void* data, unsigned int vCount)
	: layout(lt), vertexData(data), vertexCount(vCount) {
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->vertexCount * this->layout.vertexSize(), data, GL_STATIC_DRAW);
}

apr::Mesh::~Mesh() {
	glDeleteBuffers(1, &this->VBO);
}

void apr::Mesh::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	unsigned long typeSize = sizeof(float);
	unsigned int offset = 0;

	for (unsigned int i = 0; i < this->layout.numElements(); i++) {
		unsigned int elementSize = this->layout.getElement(i).size;
		unsigned long stride = offset * typeSize;

		glVertexAttribPointer(i, elementSize, GL_FLOAT, GL_FALSE, this->layout.vertexSize(), reinterpret_cast<void*>(stride));
		glEnableVertexAttribArray(i);

		offset += elementSize;
	}
}

unsigned int apr::Mesh::getVertexCount() const {
	return this->vertexCount;
}

unsigned int apr::VertexLayout::vertexSize() const {
	unsigned int size = 0;
	for (unsigned int i = 0; i < this->numElements(); i++) {
		size += this->getElement(i).size;
	}
	return size * static_cast<unsigned int>(sizeof(float));
}

unsigned int apr::VertexLayout::numElements() const {
	return static_cast<unsigned int>(this->elements.size());
}

const apr::VertexElement& apr::VertexLayout::getElement(unsigned int index) const {
	return this->elements[index];
}
