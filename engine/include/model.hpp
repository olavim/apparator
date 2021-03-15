#pragma once

#include <vector>
#include "mesh.hpp"
#include "material.hpp"
#include "drawable.hpp"

class aiScene;
class aiNode;

namespace apparator {
	class Camera;

	struct ModelPart {
		const Mesh* mesh;
		const Material* material;
		ModelPart(const Mesh* m, const Material* mat) : mesh(m), material(mat) {};
	};

	class Model : public Drawable {
		public:
			Model();
			Model(std::string modelPath);
			~Model();

			void addPart(const ModelPart& part);
			void addPart(const ModelPart& part) const;

			void draw(const Camera* camera) const;

			std::vector<ModelPart> parts;
		private:
			void processNode(aiNode *node, const aiScene *scene, std::string modelDirectory);
	};
}
