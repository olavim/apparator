#include <GLFW/glfw3.h>
#include <cmath>
#include "input.hpp"

using namespace apparator;

void input::InputManager::cursorPosCallback(GLFWwindow *window, double x, double y) {
	input::InputManager *mim = static_cast<input::InputManager*>(glfwGetWindowUserPointer(window));
	mim->mouseX = x;
	mim->mouseY = y;
}

void input::InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	(void)scancode;
	(void)mods;
	input::InputManager *mim = static_cast<input::InputManager*>(glfwGetWindowUserPointer(window));
	mim->keyState[key] = action;
}

input::InputManager::InputManager(GLFWwindow *win) {
	this->window = win;

	glfwSetWindowUserPointer(this->window, this);
	glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GL_TRUE);

	glfwSetCursorPosCallback(this->window, input::InputManager::cursorPosCallback);
	glfwSetKeyCallback(this->window, input::InputManager::keyCallback);

	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);
	this->mouseTickX = this->mouseX;
	this->mouseTickY = this->mouseY;
}

input::InputManager::~InputManager() {
	glfwSetCursorPosCallback(this->window, NULL);
	glfwSetKeyCallback(this->window, NULL);
}

void input::InputManager::setCursorMode(const int mode) {
	glfwSetInputMode(window, GLFW_CURSOR, mode);
}

void input::InputManager::setAxisLabel(const char* label, int negativeKey, int positiveKey) {
	this->keyAxisLabel[label] = {negativeKey, positiveKey};
}

void input::InputManager::setAxisLabel(const char* label, int joystickAxis) {
	this->joystickAxisLabel[label] = joystickAxis;
}

void input::InputManager::update() {
	this->mouseDeltaX = this->mouseX - this->mouseTickX;
	this->mouseDeltaY = this->mouseY - this->mouseTickY;
	this->mouseTickX = mouseX;
	this->mouseTickY = mouseY;
}

double input::InputManager::getMouseX() {
	return this->mouseTickX;
}

double input::InputManager::getMouseY() {
	return this->mouseTickY;
}

double input::InputManager::getMouseDeltaX() {
	return this->mouseDeltaX;
}

double input::InputManager::getMouseDeltaY() {
	return this->mouseDeltaY;
}

float input::InputManager::getAxis(const char* label) {
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

float input::InputManager::getAxis(const char* label, int joystick) {
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
