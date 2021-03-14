#include "drawable.hpp"
#include "camera.hpp"
#include "node.hpp"

namespace apr = apparator;

apr::Drawable::Drawable() {
}

apr::Drawable::~Drawable() {
}

void apr::Drawable::setNode(Node *node) {
	this->node = node;
}

void apr::Drawable::draw(const Camera* camera) {
}
