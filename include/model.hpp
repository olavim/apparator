#include <vector>
#include "mesh.hpp"
#include "texture.hpp"
#include "material.hpp"
#include "transform.hpp"

namespace apparator {
	class Model {
		public:
			Model(const Mesh& m) : mesh(m) {};

			void addTexture(const Texture* texture);
			void addMaterial(const Material* material);
			void draw();

			Transform transform;
			const Mesh& mesh;
			std::vector<const Texture*> textures;
			std::vector<const Material*> materials;
	};
}
