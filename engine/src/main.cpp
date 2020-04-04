#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "math.hpp"
#include "camera.hpp"
#include "input.hpp"
#include "resources.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "material.hpp"
#include "model.hpp"

using namespace apparator;

static const float window_width = 1024;
static const float window_height = 768;

// Position, normal, texture coordinates
static const float vertexData[] = {
	// left - br,bl,tl
	-1.0f,-1.0f,-1.0f,-1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	-1.0f,-1.0f, 1.0f,-1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	-1.0f, 1.0f, 1.0f,-1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	// left - br,tl,tr
	-1.0f,-1.0f,-1.0f,-1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, 1.0f,-1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,-1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	// front - tr,bl,tl
	 1.0f, 1.0f,-1.0f, 0.0f, 0.0f,-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f, 0.0f, 0.0f,-1.0f, 0.0f, 0.0f,
	-1.0f, 1.0f,-1.0f, 0.0f, 0.0f,-1.0f, 0.0f, 1.0f,
	// front - tr,br,bl
	 1.0f, 1.0f,-1.0f, 0.0f, 0.0f,-1.0f, 1.0f, 1.0f,
	 1.0f,-1.0f,-1.0f, 0.0f, 0.0f,-1.0f, 1.0f, 0.0f,
	-1.0f,-1.0f,-1.0f, 0.0f, 0.0f,-1.0f, 0.0f, 0.0f,
	// bottom - tr,bl,br
	 1.0f,-1.0f, 1.0f, 0.0f,-1.0f, 0.0f, 1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f, 0.0f,-1.0f, 0.0f, 0.0f, 0.0f,
	 1.0f,-1.0f,-1.0f, 0.0f,-1.0f, 0.0f, 1.0f, 0.0f,
	// bottom - tr,tl,bl
	 1.0f,-1.0f, 1.0f, 0.0f,-1.0f, 0.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f, 0.0f,-1.0f, 0.0f, 0.0f, 1.0f,
	-1.0f,-1.0f,-1.0f, 0.0f,-1.0f, 0.0f, 0.0f, 0.0f,
	// back - tr,br,bl
	-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	 1.0f,-1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	// back - tl,tr,bl
	 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	 1.0f,-1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	// right - tr,bl,tl
	 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	 1.0f,-1.0f,-1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	 1.0f, 1.0f,-1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	// right - bl,tr,br
	 1.0f,-1.0f,-1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	 1.0f,-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	// top - tr,br,bl
	 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	 1.0f, 1.0f,-1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-1.0f, 1.0f,-1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	// top - tr,bl,tl
	 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
};

Vector3 cubePositions[] = {
	Vector3( 0.0f, 0.0f, 0.0f),
	Vector3( 2.0f, 5.0f,-15.0f),
	Vector3(-10.5f,-20.2f,-2.5f),
	Vector3(-3.8f,-2.0f,-12.3f),
	Vector3( 2.4f,-0.4f,-3.5f),
	Vector3(-10.7f, 3.0f,-7.5f),
	Vector3( 10.3f,-10.0f,-2.5f),
	Vector3( 10.5f, 2.0f,-2.5f),
	Vector3( 10.5f, -2.0f,-1.5f),
	Vector3(-1.3f, 1.0f,-10.5f),
	Vector3( 0.0f, 5.0f, 5.0f),
	Vector3( 2.0f, 10.0f,-15.0f),
	Vector3(-1.5f,-7.2f,-7.5f),
	Vector3(-3.8f,-7.0f,-12.3f),
	Vector3( 2.4f,-5.4f,-3.5f),
	Vector3(-1.7f, 8.0f,-7.5f),
	Vector3( 1.3f,-7.0f,-5.5f),
	Vector3( 4.5f, 7.0f,-7.5f),
	Vector3( 15.5f, 5.2f,-8.5f),
	Vector3(-15.3f, 6.0f,-4.5f),
	Vector3( 5.0f, 5.0f, 0.0f),
	Vector3( 7.0f, 10.0f,-15.0f),
	Vector3(-6.5f,-7.2f,-2.5f),
	Vector3(-8.8f,-7.0f,-12.3f),
	Vector3(-3.0f,-2.0f,-2.0f)
};

static VertexLayout vertexLayout({VertexElement(3), VertexElement(3), VertexElement(2)});

static std::vector<Material> materials = {
	Material({0.0215f, 0.1745f, 0.0215f}, {0.07568f, 0.61424f, 0.07568f}, {0.633f, 0.727811f, 0.633f}, 76.8f), // emerald
	Material({0.135f, 0.2225f, 0.1575f}, {0.54f, 0.89f, 0.63f}, {0.316228f, 0.316228f, 0.316228f}, 12.8f), // jade
	Material({0.05375f, 0.05f, 0.06625f}, {0.18275f, 0.17f, 0.22525f}, {0.332741f, 0.328634f, 0.346435f}, 38.4f), // obsidian
	Material({0.25f, 0.20725f, 0.20725f}, {1, 0.829f, 0.829f}, {0.296648f, 0.296648f, 0.296648f}, 11.264f), // pearl
	Material({0.1745f, 0.01175f, 0.01175f}, {0.61424f, 0.04136f, 0.04136f}, {0.727811f, 0.626959f, 0.626959f}, 76.8f), // ruby
	Material({0.1f, 0.18725f, 0.1745f}, {0.396f, 0.74151f, 0.69102f}, {0.297254f, 0.30829f, 0.306678f}, 12.8f), // turquoise
	Material({0.329412f, 0.223529f, 0.027451f}, {0.780392f, 0.568627f, 0.113725f}, {0.992157f, 0.941176f, 0.807843f}, 27.89743616f), // brass
	Material({0.2125f, 0.1275f, 0.054f}, {0.714f, 0.4284f, 0.18144f}, {0.393548f, 0.271906f, 0.166721f}, 25.6f), // bronze
	Material({0.25f, 0.25f, 0.25f}, {0.4f, 0.4f, 0.4f}, {0.774597f, 0.774597f, 0.774597f}, 76.8f), // chrome
	Material({0.19125f, 0.0735f, 0.0225f}, {0.7038f, 0.27048f, 0.0828f}, {0.256777f, 0.137622f, 0.086014f}, 12.8f), // copper
	Material({0.24725f, 0.1995f, 0.0745f}, {0.75164f, 0.60648f, 0.22648f}, {0.628281f, 0.555802f, 0.366065f}, 51.2f), // gold
	Material({0.19225f, 0.19225f, 0.19225f}, {0.50754f, 0.50754f, 0.50754f}, {0.508273f, 0.508273f, 0.508273f}, 51.2f), // silver
	Material({0.0f, 0.0f, 0.0f}, {0.01f, 0.01f, 0.01f}, {0.50f, 0.50f, 0.50f}, 32), // black plastic
	Material({0.0f, 0.1f, 0.06f}, {0.0f, 0.50980392f, 0.50980392f}, {0.50196078f, 0.50196078f, 0.50196078f}, 32), // cyan plastic
	Material({0.0f, 0.0f, 0.0f}, {0.1f, 0.35f, 0.1f}, {0.45f, 0.55f, 0.45f}, 32), // green plastic
	Material({0.0f, 0.0f, 0.0f}, {0.5f, 0.0f, 0.0f}, {0.7f, 0.6f, 0.6f}, 32), // red plastic
	Material({0.0f, 0.0f, 0.0f}, {0.55f, 0.55f, 0.55f}, {0.70f, 0.70f, 0.70f}, 32), // white plastic
	Material({0.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.0f}, {0.60f, 0.60f, 0.50f}, 32), // yellow plastic
	Material({0.02f, 0.02f, 0.02f}, {0.01f, 0.01f, 0.01f}, {0.4f, 0.4f, 0.4f}, 10), // black rubber
	Material({0.0f, 0.05f, 0.05f}, {0.4f, 0.5f, 0.5f}, {0.04f, 0.7f, 0.7f}, 10), // cyan rubber
	Material({0.0f, 0.05f, 0.0f}, {0.4f, 0.5f, 0.4f}, {0.04f, 0.7f, 0.04f}, 10), // green rubber
	Material({0.05f, 0.0f, 0.0f}, {0.5f, 0.4f, 0.4f}, {0.7f, 0.04f, 0.04f}, 10), // red rubber
	Material({0.05f, 0.05f, 0.05f}, {0.5f, 0.5f, 0.5f}, {0.7f, 0.7f, 0.7f}, 10), // white rubber
	Material({0.05f, 0.05f, 0.0f}, {0.5f, 0.5f, 0.4f}, {0.7f, 0.7f, 0.04f}, 10) // yellow rubber
};

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
	Shader *colorShader = resourceMgr.loadShader("colored", "resources/shaders/colored.vert", "resources/shaders/colored.frag");
	Shader *textureShader = resourceMgr.loadShader("textured", "resources/shaders/textured.vert", "resources/shaders/textured.frag");
	Texture *containerDiff = resourceMgr.loadTexture("container_diff", "resources/textures/container_diff.png");
	Texture *containerSpec = resourceMgr.loadTexture("container_spec", "resources/textures/container_spec.png");

	materials.push_back(Material({containerDiff, containerSpec, 32}));

	Mesh cubeMesh(vertexLayout, &vertexData[0], sizeof(vertexData) / sizeof(float) / 8);

	std::vector<Model> models;
	for (unsigned int i = 0; i < materials.size(); i++) {
		Model m;
		Shader *shader = materials[i].type == MaterialType::COLORED ? colorShader : textureShader;
		m.addPart({cubeMesh, materials[i], *shader});
		m.transform.translate(cubePositions[i]);
		m.transform.rotate(Quaternion(static_cast<float>(rand()), static_cast<float>(rand()), static_cast<float>(rand())));
		models.push_back(m);
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Dark blue background
	glClearColor(0.2f, 0.3f, 0.5f, 0.0f);

	InputManager inputMgr(window);
	inputMgr.setAxisLabel("moveX", GLFW_KEY_A, GLFW_KEY_D);
	inputMgr.setAxisLabel("moveY", GLFW_KEY_LEFT_SHIFT, GLFW_KEY_SPACE);
	inputMgr.setAxisLabel("moveZ", GLFW_KEY_W, GLFW_KEY_S);
	inputMgr.setKeyLabel("quit", GLFW_KEY_ESCAPE);
	inputMgr.setKeyLabel("changeCamera", GLFW_KEY_ENTER);

	float aspect = window_width / window_height;
	PerspectiveCamera pCamera(90, aspect);
	OrtographicCamera oCamera(-5 * aspect, 5 * aspect, -5, 5);

	pCamera.transform.translate(-4, 4, 4);
	pCamera.transform.setRotation(Quaternion::lookAt(pCamera.transform.translation(), Vector3(0, 1, 0)));
	oCamera.transform.translate(-4, 4, 4);
	oCamera.transform.setRotation(Quaternion::lookAt(oCamera.transform.translation(), Vector3(0, 1, 0)));

	Camera *activeCamera = &pCamera;

	double lastTime = glfwGetTime();
	float speed = 10;
	float mouseSensitivity = 0.001f;

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
			Quaternion yaw(Vector3(0, 1, 0), mouseSensitivity * -static_cast<float>(inputMgr.getMouseDeltaX()));
			Quaternion pitch(activeCamera->transform.right(), mouseSensitivity * -static_cast<float>(inputMgr.getMouseDeltaY()));
			activeCamera->transform.rotate(yaw * pitch);

			// model.transform.setScale((3 + sin(currentTime)) / 4, 1, 1);

			for (unsigned int i = 0; i < models.size(); i++) {
				// Draw model
				models[i].draw(activeCamera);
			}

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
