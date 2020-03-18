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

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

	shaders::ShaderProgram shaders("shaders/vertex.glsl", "shaders/fragment.glsl");

	// Cube
	GLfloat vertexBufferData[] = {
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

	GLfloat colorBufferData[] = {
		0.583f, 0.771f, 0.014f,
		0.609f, 0.115f, 0.436f,
		0.327f, 0.483f, 0.844f,
		0.822f, 0.569f, 0.201f,
		0.435f, 0.602f, 0.223f,
		0.310f, 0.747f, 0.185f,
		0.597f, 0.770f, 0.761f,
		0.559f, 0.436f, 0.730f,
		0.359f, 0.583f, 0.152f,
		0.483f, 0.596f, 0.789f,
		0.559f, 0.861f, 0.639f,
		0.195f, 0.548f, 0.859f,
		0.014f, 0.184f, 0.576f,
		0.771f, 0.328f, 0.970f,
		0.406f, 0.615f, 0.116f,
		0.676f, 0.977f, 0.133f,
		0.971f, 0.572f, 0.833f,
		0.140f, 0.616f, 0.489f,
		0.997f, 0.513f, 0.064f,
		0.945f, 0.719f, 0.592f,
		0.543f, 0.021f, 0.978f,
		0.279f, 0.317f, 0.505f,
		0.167f, 0.620f, 0.077f,
		0.347f, 0.857f, 0.137f,
		0.055f, 0.953f, 0.042f,
		0.714f, 0.505f, 0.345f,
		0.783f, 0.290f, 0.734f,
		0.722f, 0.645f, 0.174f,
		0.302f, 0.455f, 0.848f,
		0.225f, 0.587f, 0.040f,
		0.517f, 0.713f, 0.338f,
		0.053f, 0.959f, 0.120f,
		0.393f, 0.621f, 0.362f,
		0.673f, 0.211f, 0.457f,
		0.820f, 0.883f, 0.371f,
		0.982f, 0.099f, 0.879f
	};

	// Create vertex array object
	GLuint vertexArray;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

	GLuint colorBuffer;
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorBufferData), colorBufferData, GL_STATIC_DRAW);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	input::InputManager inputMgr(window);
	inputMgr.setCursorMode(CURSOR_MODE_CAPTURED);
	inputMgr.setAxisLabel("moveX", GLFW_KEY_A, GLFW_KEY_D);
	inputMgr.setAxisLabel("moveY", GLFW_KEY_LEFT_SHIFT, GLFW_KEY_SPACE);
	inputMgr.setAxisLabel("moveZ", GLFW_KEY_W, GLFW_KEY_S);

	camera::PerspectiveCamera camera(90, window_width / window_height, 0.1, 100);
	camera.move(math::vec3(0, 0, 5));

	GLuint matrixId = shaders.uniformLocation("MVP");

	double lastTime = glfwGetTime();
	double speed = 3;
	double mouseSensitivity = 0.001;

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)) {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		inputMgr.update();

		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);
		lastTime = currentTime;

		shaders.use();

		math::vec3 position;
		position -= camera.right() * deltaTime * speed * inputMgr.getAxis("moveX");
		position -= camera.up() * deltaTime * speed * inputMgr.getAxis("moveY");
		position -= camera.forward() * deltaTime * speed * inputMgr.getAxis("moveZ");
		camera.move(position);

		camera.rotate(
			mouseSensitivity * inputMgr.getMouseDeltaX(),
			mouseSensitivity * inputMgr.getMouseDeltaY()
		);

		math::mat4 mvp = camera.getTransform() * math::mat4(1);

		glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);

		// Draw triangle
		int numVertices = sizeof(vertexBufferData) / sizeof(*vertexBufferData) / 3;

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(0));

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(0));

		glDrawArrays(GL_TRIANGLES, 0, numVertices);
		glDisableVertexAttribArray(0);

		// GLFW uses double buffering. Here we swap the buffer we render to with the one that is displayed.
		glfwSwapBuffers(window);

		// Update window events, such as key presses
		glfwPollEvents();
	}

	// Cleanup
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &colorBuffer);
	glDeleteVertexArrays(1, &vertexArray);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
