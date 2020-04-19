#pragma once

#include <vector>

class aiMesh;

namespace apparator {
	struct VertexElement {
		unsigned int size;
		VertexElement(unsigned int s) : size(s) {};
	};

	class VertexLayout {
		public:
			VertexLayout(std::vector<VertexElement> e) : elements(e) {};
			VertexLayout() : elements() {};

			unsigned int vertexSize() const;
			size_t numElements() const;

			void addElement(const VertexElement& e);
			const VertexElement& getElement(unsigned int index) const;

			VertexLayout& operator=(const VertexLayout& other);
		private:
			std::vector<VertexElement> elements;
	};

	class Mesh {
		public:
			Mesh(const VertexLayout& layout, std::vector<float> vertexData);
			Mesh(const aiMesh* mesh);
			Mesh(const Mesh& mesh);
			~Mesh();

			unsigned int getVertexCount() const;
			void bind() const;
		private:
			VertexLayout layout;
			std::vector<float> vertexData;
			unsigned int VBO;
	};
}
