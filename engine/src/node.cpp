#include "node.hpp"
#include "drawable.hpp"

namespace apr = apparator;

apr::Node::Node() {
}

apr::Node::~Node() {
}

void apr::Node::addChild(Node *node) {
	node->parent = this;
	this->children.push_back(node);
}

void apr::Node::setDrawable(Drawable *drawable) {
	this->_drawable = drawable;
	this->_drawable->setNode(this);
}

apr::Drawable* apr::Node::drawable() {
	return this->_drawable;
}

const apr::Drawable* apr::Node::drawable() const {
	return this->_drawable;
}

apr::Transform& apr::Node::transform() {
	return this->_transform;
}

const apr::Transform& apr::Node::transform() const {
	return this->_transform;
}

apr::Transform apr::Node::globalTransform() const {
	if (this->parent) {
		return this->parent->globalTransform() * this->_transform;
	}

	return this->_transform;
}
