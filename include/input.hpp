#pragma once

#include <GLFW/glfw3.h>

#define CURSOR_MODE_CAPTURED GLFW_CURSOR_DISABLED

namespace apparator {
	namespace input {
		class MouseInputManager {
				static void cursorPosCallback(GLFWwindow *window, double x, double y);

				GLFWwindow *window;
				double mouseX = 0;
				double mouseY = 0;
				double mouseTickX = 0;
				double mouseTickY = 0;
				double mouseDeltaX = 0;
				double mouseDeltaY = 0;
			public:
				MouseInputManager(GLFWwindow *window);
				~MouseInputManager();
				void update();
				void setCursorMode(const int mode);
				double getMouseX();
				double getMouseY();
				double getMouseDeltaX();
				double getMouseDeltaY();
		};
	}
}
