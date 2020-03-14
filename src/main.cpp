#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <shaders.hpp>

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
	window = glfwCreateWindow(1024, 768, "Apparator", NULL, NULL);

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
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	apparator::shaders::ShaderProgram shaders("shaders/vertex.glsl", "shaders/fragment.glsl");

	// Create triangle
	GLfloat vertexBufferData[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)) {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		shaders.use();

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

	return 0;
}
