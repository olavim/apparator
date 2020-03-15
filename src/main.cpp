#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shaders.hpp"
#include "math.hpp"
#include "camera.hpp"
#include "input.hpp"

using namespace apparator;

static const float window_width = 1024;
static const float window_height = 768;

int main() {
	// Initialise GLFW
	if(!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

	// We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// We don't want the old OpenGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	GLFWwindow* window;
	window = glfwCreateWindow(window_width, window_height, "Apparator", NULL, NULL);

	if (!window) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return -1;
	}

	// Tell GLFW which window is in use
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum glewStatus = glewInit();
	if (glewStatus != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glewStatus));
		return -1;
	}

	// Create vertex array object
	GLuint vertexArrayId;
	glGenVertexArrays(1, &vertexArrayId);
	glBindVertexArray(vertexArrayId);

	shaders::ShaderProgram shaders("shaders/vertex.glsl", "shaders/fragment.glsl");

	// Create triangle
	GLfloat vertexBufferData[] = {
		-1.0f, -1.0f, 0.1f,
		1.0f, -1.0f, 0.1f,
		0.0f, 1.0f, 0.1f,
	};

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	input::MouseInputManager mim(window);
	mim.setCursorMode(CURSOR_MODE_CAPTURED);

	camera::PerspectiveCamera camera(90, window_width / window_height, 0.1, 100);
	camera.move(math::vec3(0, 0, 5));

	GLuint matrixId = shaders.uniformLocation("MVP");

	double lastTime = glfwGetTime();
	double speed = 3;

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)) {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);
		mim.update();

		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);
		lastTime = currentTime;

		shaders.use();

		math::vec3 position;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			position += camera.forward() * deltaTime * speed;
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			position -= camera.forward() * deltaTime * speed;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			position += camera.right() * deltaTime * speed;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			position -= camera.right() * deltaTime * speed;
		}

		camera.move(position);
		camera.rotate(
			0.0005 * -mim.getMouseDeltaX(),
			0.0005 * -mim.getMouseDeltaY()
		);

		math::mat4 mvp = camera.getTransform() * math::mat4(1);

		glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);

		// Draw triangle
		int numVertices = sizeof(vertexBufferData) / sizeof(*vertexBufferData) / 3;

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(
			0, // Attribute 0. No particular reason for 0, but must match the layout in the shader.
			numVertices,
			GL_FLOAT, // Type
			GL_FALSE, // Normalized?
			0, // Stride
			static_cast<void*>(0) // Array buffer offset
		);
		glDrawArrays(GL_TRIANGLES, 0, numVertices);
		glDisableVertexAttribArray(0);

		// GLFW uses double buffering. Here we swap the buffer we render to with the one that is displayed.
		glfwSwapBuffers(window);

		// Update window events, such as key presses
		glfwPollEvents();
	}

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &vertexArrayId);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
