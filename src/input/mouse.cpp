#include <GLFW/glfw3.h>

#include "input.hpp"

using namespace apparator;

void input::MouseInputManager::cursorPosCallback(GLFWwindow *window, double x, double y) {
	input::MouseInputManager *mim = static_cast<MouseInputManager*>(glfwGetWindowUserPointer(window));
	mim->mouseX = x;
	mim->mouseY = y;
}

input::MouseInputManager::MouseInputManager(GLFWwindow *win) {
	this->window = win;

	glfwSetWindowUserPointer(this->window, this);
	glfwSetCursorPosCallback(this->window, input::MouseInputManager::cursorPosCallback);
}

input::MouseInputManager::~MouseInputManager() {
	glfwSetCursorPosCallback(this->window, NULL);
}

void input::MouseInputManager::setCursorMode(const int mode) {
	glfwSetInputMode(window, GLFW_CURSOR, mode);
}

void input::MouseInputManager::update() {
	this->mouseDeltaX = this->mouseX - this->mouseTickX;
	this->mouseDeltaY = this->mouseY - this->mouseTickY;
	this->mouseTickX = mouseX;
	this->mouseTickY = mouseY;
}

double input::MouseInputManager::getMouseX() {
	return this->mouseTickX;
}

double input::MouseInputManager::getMouseY() {
	return this->mouseTickY;
}

double input::MouseInputManager::getMouseDeltaX() {
	return this->mouseDeltaX;
}

double input::MouseInputManager::getMouseDeltaY() {
	return this->mouseDeltaY;
}
