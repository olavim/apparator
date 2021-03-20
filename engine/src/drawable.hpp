#pragma once

#include <vector>
#include "renderer/camera.hpp"
#include "drawable.hpp"
#include "node.hpp"

namespace apparator {
	class Node;

	class Drawable {
		public:
			Drawable();
			~Drawable();

			void setNode(Node* node);
			virtual void draw(const Camera* camera) const;

		protected:
			Node* node = nullptr;
	};
}
