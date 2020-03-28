#pragma once

#include <vector>
#include "camera.hpp"
#include "mesh.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "transform.hpp"

namespace apparator {
	struct ModelPart {
		const Mesh& mesh;
		const Texture& texture;
		const Shader& shader;
		ModelPart(const Mesh& m, const Texture& t, const Shader& s) : mesh(m), texture(t), shader(s) {};
	};

	class Model {
		public:
			void addPart(const ModelPart& part);
			void draw(const Camera* camera);

			Transform transform;
			std::vector<ModelPart> parts;
	};
}
