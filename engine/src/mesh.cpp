#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <assimp/scene.h>

#include "mesh.hpp"

namespace apr = apparator;

apr::Mesh::Mesh(const apr::VertexLayout& lt, std::vector<float> data) : layout(lt), vertexData(data) {
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->vertexData.size() * sizeof(float), &this->vertexData[0], GL_STATIC_DRAW);
}

apr::Mesh::Mesh(const aiMesh* mesh) {
	apr::VertexLayout vertexLayout({apr::VertexElement(3), apr::VertexElement(3)});

	if (mesh->mTextureCoords[0]) {
		vertexLayout.addElement(apr::VertexElement(2));
	}

	std::vector<float> data;

	for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
		data.push_back(mesh->mVertices[j].x);
		data.push_back(mesh->mVertices[j].y);
		data.push_back(mesh->mVertices[j].z);
		data.push_back(mesh->mNormals[j].x);
		data.push_back(mesh->mNormals[j].y);
		data.push_back(mesh->mNormals[j].z);

		if (mesh->mTextureCoords[0]) {
			data.push_back(mesh->mTextureCoords[0][j].x);
			data.push_back(mesh->mTextureCoords[0][j].y);
		}
	}

	this->layout = vertexLayout;
	this->vertexData = data;

	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->vertexData.size() * sizeof(float), &this->vertexData[0], GL_STATIC_DRAW);
}

apr::Mesh::Mesh(const Mesh& mesh) {
	this->layout = mesh.layout;
	this->vertexData = mesh.vertexData;
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->vertexData.size() * sizeof(float), &this->vertexData[0], GL_STATIC_DRAW);
}

apr::Mesh::~Mesh() {
	glDeleteBuffers(1, &this->VBO);
}

void apr::Mesh::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	unsigned long typeSize = sizeof(float);
	unsigned long long offset = 0;

	for (unsigned int i = 0; i < this->layout.numElements(); i++) {
		apr::VertexElement e = this->layout.getElement(i);
		unsigned int elementSize = e.size;
		unsigned long long stride = offset * typeSize;

		glVertexAttribPointer(i, elementSize, GL_FLOAT, GL_FALSE, this->layout.vertexSize(), reinterpret_cast<void*>(stride));
		glEnableVertexAttribArray(i);

		offset += elementSize;
	}
}

unsigned int apr::Mesh::getVertexCount() const {
	unsigned int layoutSize = 0;
	for (unsigned int i = 0; i < this->layout.numElements(); i++) {
		layoutSize += this->layout.getElement(i).size;
	}

	return this->vertexData.size() / layoutSize;
}

unsigned int apr::VertexLayout::vertexSize() const {
	unsigned int size = 0;
	for (unsigned int i = 0; i < this->numElements(); i++) {
		size += this->getElement(i).size;
	}
	return size * static_cast<unsigned int>(sizeof(float));
}

size_t apr::VertexLayout::numElements() const {
	return this->elements.size();
}

void apr::VertexLayout::addElement(const apr::VertexElement& element) {
	this->elements.push_back(element);
}

const apr::VertexElement& apr::VertexLayout::getElement(unsigned int index) const {
	size_t s = this->elements.size();
	return this->elements.at(index);
}

apr::VertexLayout& apr::VertexLayout::operator=(const apr::VertexLayout& other) {
	this->elements = other.elements;
}
