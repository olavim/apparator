#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "math.hpp"
#include "camera.hpp"
#include "input.hpp"
#include "resources.hpp"
#include "mesh.hpp"
#include "material.hpp"
#include "texture.hpp"
#include "model.hpp"

using namespace apparator;

static const float window_width = 1024;
static const float window_height = 768;

static const float vertexData[] = {
	// left - br,bl,tl
	-1.0f,-1.0f,-1.0f, 1, 1, 1, 1.0f, 0.0f,
	-1.0f,-1.0f, 1.0f, 1, 1, 1, 0.0f, 0.0f,
	-1.0f, 1.0f, 1.0f, 1, 1, 1, 0.0f, 1.0f,
	// left - br,tl,tr
	-1.0f,-1.0f,-1.0f, 1, 1, 1, 1.0f, 0.0f,
	-1.0f, 1.0f, 1.0f, 1, 1, 1, 0.0f, 1.0f,
	-1.0f, 1.0f,-1.0f, 1, 1, 1, 1.0f, 1.0f,
	// front - tr,bl,tl
	 1.0f, 1.0f,-1.0f, 1, 1, 1, 1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f, 1, 1, 1, 0.0f, 0.0f,
	-1.0f, 1.0f,-1.0f, 1, 1, 1, 0.0f, 1.0f,
	// front - tr,br,bl
	 1.0f, 1.0f,-1.0f, 1, 1, 1, 1.0f, 1.0f,
	 1.0f,-1.0f,-1.0f, 1, 1, 1, 1.0f, 0.0f,
	-1.0f,-1.0f,-1.0f, 1, 1, 1, 0.0f, 0.0f,
	// bottom - tr,bl,br
	 1.0f,-1.0f, 1.0f, 1, 1, 1, 1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f, 1, 1, 1, 0.0f, 0.0f,
	 1.0f,-1.0f,-1.0f, 1, 1, 1, 1.0f, 0.0f,
	// bottom - tr,tl,bl
	 1.0f,-1.0f, 1.0f, 1, 1, 1, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f, 1, 1, 1, 0.0f, 1.0f,
	-1.0f,-1.0f,-1.0f, 1, 1, 1, 0.0f, 0.0f,
	// back - tr,br,bl
	-1.0f, 1.0f, 1.0f, 1, 1, 1, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f, 1, 1, 1, 1.0f, 0.0f,
	 1.0f,-1.0f, 1.0f, 1, 1, 1, 0.0f, 0.0f,
	// back - tl,tr,bl
	 1.0f, 1.0f, 1.0f, 1, 1, 1, 0.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, 1, 1, 1, 1.0f, 1.0f,
	 1.0f,-1.0f, 1.0f, 1, 1, 1, 0.0f, 0.0f,
	// right - tr,bl,tl
	 1.0f, 1.0f, 1.0f, 1, 1, 1, 1.0f, 1.0f,
	 1.0f,-1.0f,-1.0f, 1, 1, 1, 0.0f, 0.0f,
	 1.0f, 1.0f,-1.0f, 1, 1, 1, 0.0f, 1.0f,
	// right - bl,tr,br
	 1.0f,-1.0f,-1.0f, 1, 1, 1, 0.0f, 0.0f,
	 1.0f, 1.0f, 1.0f, 1, 1, 1, 1.0f, 1.0f,
	 1.0f,-1.0f, 1.0f, 1, 1, 1, 1.0f, 0.0f,
	// top - tr,br,bl
	 1.0f, 1.0f, 1.0f, 1, 1, 1, 1.0f, 1.0f,
	 1.0f, 1.0f,-1.0f, 1, 1, 1, 1.0f, 0.0f,
	-1.0f, 1.0f,-1.0f, 1, 1, 1, 0.0f, 0.0f,
	// top - tr,bl,tl
	 1.0f, 1.0f, 1.0f, 1, 1, 1, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f, 1, 1, 1, 0.0f, 0.0f,
	-1.0f, 1.0f, 1.0f, 1, 1, 1, 0.0f, 1.0f
};

VertexLayout vertexLayout({VertexElement(3), VertexElement(3), VertexElement(2)});

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
	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Apparator", NULL, NULL);

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
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	ResourceManager resourceMgr;
	Material *material = resourceMgr.loadMaterial("default", "shaders/vertex.glsl", "shaders/fragment.glsl");
	Texture *texture = resourceMgr.loadTexture("wall", "textures/wall.jpg");

	Mesh mesh(vertexLayout, sizeof(vertexData) / sizeof(float) / 8);
	mesh.setVertexData(&vertexData[0]);
	mesh.addPart(sizeof(vertexData) / sizeof(float) / 8);

	Model model(mesh);
	model.addTexture(texture);
	model.addMaterial(material);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	InputManager inputMgr(window);
	inputMgr.setAxisLabel("moveX", GLFW_KEY_A, GLFW_KEY_D);
	inputMgr.setAxisLabel("moveY", GLFW_KEY_LEFT_SHIFT, GLFW_KEY_SPACE);
	inputMgr.setAxisLabel("moveZ", GLFW_KEY_W, GLFW_KEY_S);

	float aspect = window_width / window_height;
	PerspectiveCamera camera(90, aspect);
	// OrtographicCamera camera(-5 * aspect, 5 * aspect, -5, 5);
	camera.transform.translate(0, 0, 5);

	unsigned int matrixId = material->uniformLocation("MVP");

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

		Vector3 position(inputMgr.getAxis("moveX"), inputMgr.getAxis("moveY"), inputMgr.getAxis("moveZ"));
		camera.transform.translate(position * deltaTime * speed);

		Quaternion yaw(Vector3(0, 1, 0), mouseSensitivity * -inputMgr.getMouseDeltaX());
		Quaternion pitch(camera.transform.right(), mouseSensitivity * -inputMgr.getMouseDeltaY());
		camera.transform.rotate(yaw * pitch);

		model.transform.setScale((3 + sin(currentTime)) / 4, 1, 1);

		Matrix4 mvp = model.transform.matrix() * camera.matrix();

		glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp.m[0]);

		model.draw();

		// GLFW uses double buffering. Here we swap the buffer we render to with the one that is displayed.
		glfwSwapBuffers(window);
		// Update window events, such as key presses
		glfwPollEvents();
	}

	// Cleanup
	glDeleteVertexArrays(1, &VAO);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
