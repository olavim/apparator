#pragma once

#include <vector>
#include <unordered_map>
#include <GLFW/glfw3.h>

#define CURSOR_MODE_CAPTURED GLFW_CURSOR_DISABLED

#define AXIS_TYPE_KEY 1
#define AXIS_TYPE_JOYSTICK 2

namespace apparator {
	namespace input {
		struct KeyAxis {
			int negativeKey;
			int positiveKey;
		};

		class InputManager {
				static void cursorPosCallback(GLFWwindow *window, double x, double y);
				static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

				GLFWwindow *window;
				double mouseX = 0;
				double mouseY = 0;
				double mouseTickX = 0;
				double mouseTickY = 0;
				double mouseDeltaX = 0;
				double mouseDeltaY = 0;

				int keyState[GLFW_KEY_LAST + 1];
				float* joystickAxes[GLFW_JOYSTICK_LAST + 1];

				std::unordered_map<const char*, KeyAxis> keyAxisLabel;
				std::unordered_map<const char*, int> joystickAxisLabel;
			public:
				InputManager(GLFWwindow *window);
				~InputManager();
				void update();
				void setCursorMode(const int mode);
				void setAxisLabel(const char* label, int negativeKey, int positiveKey);
				void setAxisLabel(const char* label, int joystickAxis);
				double getMouseX();
				double getMouseY();
				double getMouseDeltaX();
				double getMouseDeltaY();
				float getAxis(const char* label);
				float getAxis(const char* label, int joystick);
		};
	}
}
