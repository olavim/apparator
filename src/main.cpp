#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shaders.hpp"
#include "math.hpp"
#include "camera.hpp"

using namespace apparator;

static const int window_width = 1024;
static const int window_height = 768;

int main(int argc, const char * argv[]) {
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

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwPollEvents();
	glfwSetCursorPos(window, window_width / 2, window_height / 2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	camera::PerspectiveCamera camera(90, (float) window_width / (float) window_height, 0.1, 100);
	camera.move(math::vec3(0, 0, 5));

	GLuint matrixId = shaders.uniformLocation("MVP");

	double lastTime = glfwGetTime();
	double prevMouseX = 0;
	double prevMouseY = 0;
	double mouseX;
	double mouseY;

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)) {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);
		lastTime = currentTime;

		glfwGetCursorPos(window, &mouseX, &mouseY);

		double mouseXDelta = prevMouseX - mouseX;
		double mouseYDelta = prevMouseY - mouseY;
		prevMouseX = mouseX;
		prevMouseY = mouseY;

		shaders.use();

		GLfloat moveX = 0;
		GLfloat moveY = 0;
		GLfloat moveZ = 0;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			moveY = 0.1;
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			moveY = -0.1;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			moveX = -0.1;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			moveX = 0.1;
		}

		camera.move(math::vec3(moveX, moveY, moveZ));
		camera.rotate(
			0.0005 * mouseXDelta,
			0.0005 * mouseYDelta
		);

		math::mat4 model = math::mat4(1);
		math::mat4 mvp = camera.getTransform() * math::mat4(1);

		// math::Mat4 mat = mvp;
		// printf("%f, %f, %f, %f\n", mat[0][0], mat[0][1], mat[0][2], mat[0][3]);
		// printf("%f, %f, %f, %f\n", mat[1][0], mat[1][1], mat[1][2], mat[1][3]);
		// printf("%f, %f, %f, %f\n", mat[2][0], mat[2][1], mat[2][2], mat[2][3]);
		// printf("%f, %f, %f, %f\n\n", mat[3][0], mat[3][1], mat[3][2], mat[3][3]);

		// GLfloat *p = &mvp[0][0];
		// printf("%f, %f, %f, %f\n", *(p + 0), *(p + 1), *(p + 2), *(p + 3));
		// printf("%f, %f, %f, %f\n", *(p + 4), *(p + 5), *(p + 6), *(p + 7));
		// printf("%f, %f, %f, %f\n\n", *(p + 8), *(p + 9), *(p + 10), *(p + 11));

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
			(void*)0 // Array buffer offset
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
	shaders.deleteProgram();

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
