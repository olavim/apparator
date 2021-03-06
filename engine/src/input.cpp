#include <GLFW/glfw3.h>
#include <cmath>
#include <string>
#include <stdexcept>
#include <iostream>
#include "input.hpp"

namespace apr = apparator;

void apr::InputManager::cursorPosCallback(GLFWwindow *window, double x, double y) {
	apr::InputManager *mim = static_cast<apr::InputManager*>(glfwGetWindowUserPointer(window));
	mim->mouseX = x;
	mim->mouseY = y;
}

void apr::InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	(void)scancode;
	(void)mods;
	apr::InputManager *mim = static_cast<apr::InputManager*>(glfwGetWindowUserPointer(window));
	mim->keyState[key] = action;
}

apr::InputManager::InputManager(GLFWwindow *win) {
	this->window = win;

	glfwSetWindowUserPointer(this->window, this);
	glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(this->window, apr::InputManager::cursorPosCallback);
	// glfwSetKeyCallback(this->window, apr::InputManager::keyCallback);

	glfwPollEvents();
	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);
	this->mouseTickX = this->mouseX;
	this->mouseTickY = this->mouseY;
}

apr::InputManager::~InputManager() {
	glfwSetCursorPosCallback(this->window, NULL);
	glfwSetKeyCallback(this->window, NULL);
}

void apr::InputManager::setCursorMode(const int mode) {
	glfwSetInputMode(window, GLFW_CURSOR, mode);
}

void apr::InputManager::setKeyLabel(std::string label, int key) {
	this->keyLabel[label] = key;
}

void apr::InputManager::setAxisLabel(std::string label, int negativeKey, int positiveKey) {
	this->keyAxisLabel[label] = {negativeKey, positiveKey};
}

void apr::InputManager::setAxisLabel(std::string label, int joystickAxis) {
	this->joystickAxisLabel[label] = joystickAxis;
}

void apr::InputManager::update() {
	this->mouseDeltaX = this->mouseX - this->mouseTickX;
	this->mouseDeltaY = this->mouseY - this->mouseTickY;
	this->mouseTickX = mouseX;
	this->mouseTickY = mouseY;
}

double apr::InputManager::getMouseX() {
	return this->mouseTickX;
}

double apr::InputManager::getMouseY() {
	return this->mouseTickY;
}

double apr::InputManager::getMouseDeltaX() {
	return this->mouseDeltaX;
}

double apr::InputManager::getMouseDeltaY() {
	return this->mouseDeltaY;
}

bool apr::InputManager::getKey(std::string label) {
	return this->getKey(label, false);
}

bool apr::InputManager::getKey(std::string label, bool pressOnly) {
	if (this->keyLabel.find(label) == this->keyLabel.end()) {
		throw std::invalid_argument("Key with label '" + label + "' does not exist");
	}

	int key = this->keyLabel[label];
	int state = glfwGetKey(this->window, key);

	bool pressed = state == GLFW_PRESS;
	bool pressedThisFrame = pressed && !this->keyState[key];

	this->keyState[key] = pressed;

	return pressOnly ? pressedThisFrame : pressed;
}

float apr::InputManager::getAxis(std::string label) {
	if (this->keyAxisLabel.find(label) == this->keyAxisLabel.end()) {
		throw std::invalid_argument("Axis with label '" + label + "' does not exist");
	}

	KeyAxis axis = this->keyAxisLabel[label];
	float value = 0;

	if (glfwGetKey(this->window, axis.negativeKey) == GLFW_PRESS) {
		value -= 1;
	}

	if (glfwGetKey(this->window, axis.positiveKey) == GLFW_PRESS) {
		value += 1;
	}

	return value;
}

float apr::InputManager::getAxis(std::string label, int joystick) {
	if (this->joystickAxisLabel.find(label) == this->joystickAxisLabel.end()) {
		throw std::invalid_argument("Joystick axis with label '" + label + "' does not exist");
	}

	int axisKey = this->joystickAxisLabel[label];

	int numAxes;
	const float* axes = glfwGetJoystickAxes(joystick, &numAxes);

	if (axes != NULL && axisKey < numAxes) {
		float value = axes[axisKey];
		return std::abs(value) < 0.1 ? 0 : value;
	}

	return 0;
}
