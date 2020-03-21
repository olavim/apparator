#include <GLFW/glfw3.h>
#include <cmath>
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

	glfwSetCursorPosCallback(this->window, apr::InputManager::cursorPosCallback);
	glfwSetKeyCallback(this->window, apr::InputManager::keyCallback);

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

void apr::InputManager::setAxisLabel(const char* label, int negativeKey, int positiveKey) {
	this->keyAxisLabel[label] = {negativeKey, positiveKey};
}

void apr::InputManager::setAxisLabel(const char* label, int joystickAxis) {
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

float apr::InputManager::getAxis(const char* label) {
	KeyAxis axis = this->keyAxisLabel[label];
	float value = 0;

	if (this->keyState[axis.negativeKey] == GLFW_PRESS || this->keyState[axis.negativeKey] == GLFW_REPEAT) {
		value -= 1;
	}

	if (this->keyState[axis.positiveKey] == GLFW_PRESS || this->keyState[axis.positiveKey] == GLFW_REPEAT) {
		value += 1;
	}

	return value;
}

float apr::InputManager::getAxis(const char* label, int joystick) {
	if (this->joystickAxisLabel.find(label) == this->joystickAxisLabel.end()) {
		// Axis with given label does not exist
		return 0;
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
