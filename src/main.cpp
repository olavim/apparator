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
	Material({0.0215, 0.1745, 0.0215}, {0.07568, 0.61424, 0.07568}, {0.633, 0.727811, 0.633}, 76.8), // emerald
	Material({0.135, 0.2225, 0.1575}, {0.54, 0.89, 0.63}, {0.316228, 0.316228, 0.316228}, 12.8), // jade
	Material({0.05375, 0.05, 0.06625}, {0.18275, 0.17, 0.22525}, {0.332741, 0.328634, 0.346435}, 38.4), // obsidian
	Material({0.25, 0.20725, 0.20725}, {1, 0.829, 0.829}, {0.296648, 0.296648, 0.296648}, 11.264), // pearl
	Material({0.1745, 0.01175, 0.01175}, {0.61424, 0.04136, 0.04136}, {0.727811, 0.626959, 0.626959}, 76.8), // ruby
	Material({0.1, 0.18725, 0.1745}, {0.396, 0.74151, 0.69102}, {0.297254, 0.30829, 0.306678}, 12.8), // turquoise
	Material({0.329412, 0.223529, 0.027451}, {0.780392, 0.568627, 0.113725}, {0.992157, 0.941176, 0.807843}, 27.89743616), // brass
	Material({0.2125, 0.1275, 0.054}, {0.714, 0.4284, 0.18144}, {0.393548, 0.271906, 0.166721}, 25.6), // bronze
	Material({0.25, 0.25, 0.25}, {0.4, 0.4, 0.4}, {0.774597, 0.774597, 0.774597}, 76.8), // chrome
	Material({0.19125, 0.0735, 0.0225}, {0.7038, 0.27048, 0.0828}, {0.256777, 0.137622, 0.086014}, 12.8), // copper
	Material({0.24725, 0.1995, 0.0745}, {0.75164, 0.60648, 0.22648}, {0.628281, 0.555802, 0.366065}, 51.2), // gold
	Material({0.19225, 0.19225, 0.19225}, {0.50754, 0.50754, 0.50754}, {0.508273, 0.508273, 0.508273}, 51.2), // silver
	Material({0.0, 0.0, 0.0}, {0.01, 0.01, 0.01}, {0.50, 0.50, 0.50}, 32), // black plastic
	Material({0.0, 0.1, 0.06}, {0.0, 0.50980392, 0.50980392}, {0.50196078, 0.50196078, 0.50196078}, 32), // cyan plastic
	Material({0.0, 0.0, 0.0}, {0.1, 0.35, 0.1}, {0.45, 0.55, 0.45}, 32), // green plastic
	Material({0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.7, 0.6, 0.6}, 32), // red plastic
	Material({0.0, 0.0, 0.0}, {0.55, 0.55, 0.55}, {0.70, 0.70, 0.70}, 32), // white plastic
	Material({0.0, 0.0, 0.0}, {0.5, 0.5, 0.0}, {0.60, 0.60, 0.50}, 32), // yellow plastic
	Material({0.02, 0.02, 0.02}, {0.01, 0.01, 0.01}, {0.4, 0.4, 0.4}, 10), // black rubber
	Material({0.0, 0.05, 0.05}, {0.4, 0.5, 0.5}, {0.04, 0.7, 0.7}, 10), // cyan rubber
	Material({0.0, 0.05, 0.0}, {0.4, 0.5, 0.4}, {0.04, 0.7, 0.04}, 10), // green rubber
	Material({0.05, 0.0, 0.0}, {0.5, 0.4, 0.4}, {0.7, 0.04, 0.04}, 10), // red rubber
	Material({0.05, 0.05, 0.05}, {0.5, 0.5, 0.5}, {0.7, 0.7, 0.7}, 10), // white rubber
	Material({0.05, 0.05, 0.0}, {0.5, 0.5, 0.4}, {0.7, 0.7, 0.04}, 10) // yellow rubber
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
	Shader *colorShader = resourceMgr.loadShader("colored", "shaders/colored.vert", "shaders/colored.frag");
	Shader *textureShader = resourceMgr.loadShader("textured", "shaders/textured.vert", "shaders/textured.frag");
	Texture *containerDiff = resourceMgr.loadTexture("container_diff", "textures/container_diff.png");
	Texture *containerSpec = resourceMgr.loadTexture("container_spec", "textures/container_spec.png");

	materials.push_back(Material({containerDiff, containerSpec, 32}));

	Mesh cubeMesh(vertexLayout, &vertexData[0], sizeof(vertexData) / sizeof(float) / 8);

	std::vector<Model> models;
	for (unsigned int i = 0; i < materials.size(); i++) {
		int cols = ceil(sqrt(materials.size()));

		Model m;
		Shader *shader = materials[i].type == MaterialType::COLORED ? colorShader : textureShader;
		m.addPart({cubeMesh, materials[i], *shader});
		m.transform.translate(cubePositions[i]);
		m.transform.rotate(Quaternion(rand(), rand(), rand()));
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
	double speed = 10;
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
