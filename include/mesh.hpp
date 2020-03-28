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

	class Mesh {
		public:
			Mesh(const VertexLayout& layout, const void* vertexData, unsigned int vertexCount);
			~Mesh();

			unsigned int getVertexCount() const;
			void bind() const;
		private:
			const VertexLayout& layout;
			const void* vertexData;
			unsigned int vertexCount;
			unsigned int VBO;
	};
}
