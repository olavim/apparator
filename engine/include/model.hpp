#pragma once

#include <vector>
#include "mesh.hpp"
#include "material.hpp"
#include "transform.hpp"

class aiScene;
class aiNode;

namespace apparator {
	class ResourceManager;
	class Camera;

	struct ModelPart {
		const Mesh* mesh;
		const Material* material;
		ModelPart(const Mesh* m, const Material* mat) : mesh(m), material(mat) {};
	};

	class Model {
		public:
			Model(std::string modelPath, ResourceManager& resMgr);
			~Model();

			void addPart(const ModelPart& part);
			void addPart(const ModelPart& part) const;

			void draw(const Camera* camera);

			Transform transform;
			std::vector<ModelPart> parts;
		private:
			void processNode(aiNode *node, const aiScene *scene, std::string modelDirectory, ResourceManager& resMgr);
	};
}
