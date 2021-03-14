#pragma once

#include <vector>
#include "drawable.hpp"
#include "camera.hpp"
#include "node.hpp"

namespace apparator {
	class Node;

	class Drawable {
		public:
			Drawable();
			~Drawable();

			void setNode(Node* node);
			virtual void draw(const Camera* camera);

		protected:
			Node* node;
	};
}
