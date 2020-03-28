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
#include "shader.hpp"
#include "texture.hpp"
#include "model.hpp"

using namespace apparator;

static const float window_width = 1024;
static const float window_height = 768;

// Position, normal, color, texture coordinates
static const float vertexData[] = {
	// left - br,bl,tl
	-1.0f,-1.0f,-1.0f,-1.0f, 0.0f, 0.0f, 1, 1, 1, 1.0f, 0.0f,
	-1.0f,-1.0f, 1.0f,-1.0f, 0.0f, 0.0f, 1, 1, 1, 0.0f, 0.0f,
	-1.0f, 1.0f, 1.0f,-1.0f, 0.0f, 0.0f, 1, 1, 1, 0.0f, 1.0f,
	// left - br,tl,tr
	-1.0f,-1.0f,-1.0f,-1.0f, 0.0f, 0.0f, 1, 1, 1, 1.0f, 0.0f,
	-1.0f, 1.0f, 1.0f,-1.0f, 0.0f, 0.0f, 1, 1, 1, 0.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,-1.0f, 0.0f, 0.0f, 1, 1, 1, 1.0f, 1.0f,
	// front - tr,bl,tl
	 1.0f, 1.0f,-1.0f, 0.0f, 0.0f,-1.0f, 1, 1, 1, 1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f, 0.0f, 0.0f,-1.0f, 1, 1, 1, 0.0f, 0.0f,
	-1.0f, 1.0f,-1.0f, 0.0f, 0.0f,-1.0f, 1, 1, 1, 0.0f, 1.0f,
	// front - tr,br,bl
	 1.0f, 1.0f,-1.0f, 0.0f, 0.0f,-1.0f, 1, 1, 1, 1.0f, 1.0f,
	 1.0f,-1.0f,-1.0f, 0.0f, 0.0f,-1.0f, 1, 1, 1, 1.0f, 0.0f,
	-1.0f,-1.0f,-1.0f, 0.0f, 0.0f,-1.0f, 1, 1, 1, 0.0f, 0.0f,
	// bottom - tr,bl,br
	 1.0f,-1.0f, 1.0f, 0.0f,-1.0f, 0.0f, 1, 1, 1, 1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f, 0.0f,-1.0f, 0.0f, 1, 1, 1, 0.0f, 0.0f,
	 1.0f,-1.0f,-1.0f, 0.0f,-1.0f, 0.0f, 1, 1, 1, 1.0f, 0.0f,
	// bottom - tr,tl,bl
	 1.0f,-1.0f, 1.0f, 0.0f,-1.0f, 0.0f, 1, 1, 1, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f, 0.0f,-1.0f, 0.0f, 1, 1, 1, 0.0f, 1.0f,
	-1.0f,-1.0f,-1.0f, 0.0f,-1.0f, 0.0f, 1, 1, 1, 0.0f, 0.0f,
	// back - tr,br,bl
	-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1, 1, 1, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1, 1, 1, 1.0f, 0.0f,
	 1.0f,-1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1, 1, 1, 0.0f, 0.0f,
	// back - tl,tr,bl
	 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1, 1, 1, 0.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1, 1, 1, 1.0f, 1.0f,
	 1.0f,-1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1, 1, 1, 0.0f, 0.0f,
	// right - tr,bl,tl
	 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1, 1, 1, 1.0f, 1.0f,
	 1.0f,-1.0f,-1.0f, 1.0f, 0.0f, 0.0f, 1, 1, 1, 0.0f, 0.0f,
	 1.0f, 1.0f,-1.0f, 1.0f, 0.0f, 0.0f, 1, 1, 1, 0.0f, 1.0f,
	// right - bl,tr,br
	 1.0f,-1.0f,-1.0f, 1.0f, 0.0f, 0.0f, 1, 1, 1, 0.0f, 0.0f,
	 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1, 1, 1, 1.0f, 1.0f,
	 1.0f,-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1, 1, 1, 1.0f, 0.0f,
	// top - tr,br,bl
	 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1, 1, 1, 1.0f, 1.0f,
	 1.0f, 1.0f,-1.0f, 0.0f, 1.0f, 0.0f, 1, 1, 1, 1.0f, 0.0f,
	-1.0f, 1.0f,-1.0f, 0.0f, 1.0f, 0.0f, 1, 1, 1, 0.0f, 0.0f,
	// top - tr,bl,tl
	 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1, 1, 1, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f, 0.0f, 1.0f, 0.0f, 1, 1, 1, 0.0f, 0.0f,
	-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1, 1, 1, 0.0f, 1.0f
};

VertexLayout vertexLayout({VertexElement(3), VertexElement(3), VertexElement(3), VertexElement(2)});

GLFWwindow* createWindow() {
	if(!glfwInit()) {
		throw std::runtime_error("Failed to initialize GLFW");
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Apparator", NULL, NULL);

	if (!window) {
		throw std::runtime_error("Failed to open GLFW window");
	}

	// Tell GLFW which window is in use
	glfwMakeContextCurrent(window);

	return window;
}

void initGlew() {
	glewExperimental = GL_TRUE;
	GLenum glewStatus = glewInit();
	if (glewStatus != GLEW_OK) {
		const char* message = reinterpret_cast<const char*>(glewGetErrorString(glewStatus));
		throw std::runtime_error(message);
	}
}

int main() {
	GLFWwindow* window = createWindow();

	initGlew();

	// Create vertex array object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	ResourceManager resourceMgr;
	Shader *shader = resourceMgr.loadShader("default", "shaders/vertex.glsl", "shaders/fragment.glsl");
	Texture *texture = resourceMgr.loadTexture("wall", "textures/wall.jpg");

	Mesh mesh(vertexLayout, &vertexData[0], sizeof(vertexData) / sizeof(float) / 11);

	Model model;
	model.addPart({mesh, *texture, *shader});

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	InputManager inputMgr(window);
	inputMgr.setAxisLabel("moveX", GLFW_KEY_A, GLFW_KEY_D);
	inputMgr.setAxisLabel("moveY", GLFW_KEY_LEFT_SHIFT, GLFW_KEY_SPACE);
	inputMgr.setAxisLabel("moveZ", GLFW_KEY_W, GLFW_KEY_S);
	inputMgr.setKeyLabel("quit", GLFW_KEY_ESCAPE);
	inputMgr.setKeyLabel("changeCamera", GLFW_KEY_ENTER);

	float aspect = window_width / window_height;
	PerspectiveCamera pCamera(90, aspect);
	OrtographicCamera oCamera(-5 * aspect, 5 * aspect, -5, 5);
	pCamera.transform.translate(0, 0, 5);

	Camera *activeCamera = &oCamera;

	double lastTime = glfwGetTime();
	double speed = 3;
	double mouseSensitivity = 0.001;

	try {
		while (!inputMgr.getKey("quit") && !glfwWindowShouldClose(window)) {
			// Clear the screen
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			if (inputMgr.getKey("changeCamera", true)) {
				activeCamera = (activeCamera == &oCamera)
					? static_cast<Camera *>(&pCamera)
					: static_cast<Camera *>(&oCamera);
			}

			double currentTime = glfwGetTime();
			float deltaTime = float(currentTime - lastTime);
			lastTime = currentTime;

			// Move camera
			Vector3 position(inputMgr.getAxis("moveX"), inputMgr.getAxis("moveY"), inputMgr.getAxis("moveZ"));
			activeCamera->transform.translate(position * deltaTime * speed);

			// Rotate camera
			Quaternion yaw(Vector3(0, 1, 0), mouseSensitivity * -inputMgr.getMouseDeltaX());
			Quaternion pitch(activeCamera->transform.right(), mouseSensitivity * -inputMgr.getMouseDeltaY());
			activeCamera->transform.rotate(yaw * pitch);

			// Scale model to get some kind of movement on the scene
			model.transform.setScale((3 + sin(currentTime)) / 4, 1, 1);

			// Draw model
			model.draw(activeCamera);

			// GLFW uses double buffering. Here we swap the buffer we render to with the one that is displayed.
			glfwSwapBuffers(window);

			// Update window events, such as key presses
			glfwPollEvents();
			inputMgr.update();
		}
	} catch (std::exception& err) {
		std::cout << "Error during game loop\n";
		std::cout << err.what() << std::endl;
	}

	// Cleanup
	glDeleteVertexArrays(1, &VAO);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
