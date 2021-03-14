#pragma once

#include <vector>
#include "transform.hpp"

namespace apparator {
	class Drawable;

	class Node {
		public:
			Node();
			~Node();

			void addChild(Node *node);
			void setDrawable(Drawable *node);

			Drawable* getDrawable();
			Drawable* getDrawable() const;

			Transform transform;
			std::vector<Node*> children;

		protected:
			Drawable *drawable;
	};
}
