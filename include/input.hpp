#pragma once

#include <string>
#include <unordered_map>
#include <GLFW/glfw3.h>

#define CURSOR_MODE_CAPTURED GLFW_CURSOR_DISABLED

#define AXIS_TYPE_KEY 1
#define AXIS_TYPE_JOYSTICK 2

namespace apparator {
	struct KeyAxis {
		int negativeKey;
		int positiveKey;
	};

	class InputManager {
			static void cursorPosCallback(GLFWwindow *window, double x, double y);
			static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		public:
			InputManager(GLFWwindow *window);
			~InputManager();

			void update();
			void setCursorMode(const int mode);
			void setKeyLabel(std::string label, int key);
			void setAxisLabel(std::string label, int negativeKey, int positiveKey);
			void setAxisLabel(std::string label, int joystickAxis);
			double getMouseX();
			double getMouseY();
			double getMouseDeltaX();
			double getMouseDeltaY();
			bool getKey(std::string label);
			bool getKey(std::string label, bool pressOnly);
			float getAxis(std::string label);
			float getAxis(std::string label, int joystick);
		private:
			GLFWwindow *window;
			double mouseX = 0;
			double mouseY = 0;
			double mouseTickX = 0;
			double mouseTickY = 0;
			double mouseDeltaX = 0;
			double mouseDeltaY = 0;

			bool keyState[GLFW_KEY_LAST + 1];
			float* joystickAxes[GLFW_JOYSTICK_LAST + 1];

			std::unordered_map<std::string, int> keyLabel;
			std::unordered_map<std::string, KeyAxis> keyAxisLabel;
			std::unordered_map<std::string, int> joystickAxisLabel;
	};
}
