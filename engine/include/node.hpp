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

			Drawable *drawable();
			const Drawable *drawable() const;

			Transform &transform();
			const Transform &transform() const;
			Transform globalTransform() const;

			std::vector<Node*> children;
			Node* parent = nullptr;

		protected:
			Drawable *_drawable = nullptr;
			Transform _transform;
	};
}
