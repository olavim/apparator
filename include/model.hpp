#pragma once

#include <vector>
#include "camera.hpp"
#include "mesh.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "material.hpp"
#include "transform.hpp"

namespace apparator {
	struct ModelPart {
		const Mesh& mesh;
		const Material& material;
		const Texture& texture;
		const Shader& shader;
		ModelPart(const Mesh& m, const Material& mat, const Texture& t, const Shader& s)
			: mesh(m), material(mat), texture(t), shader(s) {};
	};

	class Model {
		public:
			void addPart(const ModelPart& part);
			void draw(const Camera* camera);

			Transform transform;
			std::vector<ModelPart> parts;
	};
}
