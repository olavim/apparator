#include "node.hpp"
#include "drawable.hpp"

namespace apr = apparator;

apr::Node::Node() {
}

apr::Node::~Node() {
}

void apr::Node::addChild(Node *node) {
	this->children.push_back(node);
}

void apr::Node::setDrawable(Drawable *drawable) {
	this->drawable = drawable;
	this->drawable->setNode(this);
}

apr::Drawable* apr::Node::getDrawable() {
	return this->drawable;
}

apr::Drawable* apr::Node::getDrawable() const {
	return this->drawable;
}
