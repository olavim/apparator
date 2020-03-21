#pragma once

#include <vector>

namespace apparator {
	struct VertexElement {
		unsigned int size;
		VertexElement(unsigned int s) : size(s) {};
	};

	class VertexLayout {
		public:
			VertexLayout(std::vector<VertexElement> e) : elements(e) {};

			unsigned int vertexSize() const;
			unsigned int numElements() const;
			const VertexElement& getElement(unsigned int index) const;
		private:
			std::vector<VertexElement> elements;
	};

	struct MeshPart {
		unsigned int vertexCount;
		MeshPart(unsigned int vCount) : vertexCount(vCount) {};
	};

	class Mesh {
		public:
			Mesh(const VertexLayout& layout, unsigned int vertexCount);
			~Mesh();

			void setVertexData(const void* data);
			void addPart(unsigned int vertexCount);
			const MeshPart& getPart(unsigned int index) const;
			unsigned int numParts() const;
			void bind() const;
		private:
			std::vector<MeshPart> parts;
			const VertexLayout& layout;
			unsigned int vertexCount;
			unsigned int VBO;
			void* vertexData;
	};
}
