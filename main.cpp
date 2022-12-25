#define STB_IMAGE_IMPLEMENTATION
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>
#include <iostream>

#include "VulkanRenderer.h"

GLFWwindow * window;
VulkanRenderer vulkanRenderer;

void initWindow(std::string wName = "Test Window", const int width = 800, const int height = 600)
{
	// Initialise GLFW
	glfwInit();

	// Set GLFW to NOT work with OpenGL
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, wName.c_str(), nullptr, nullptr);
}


int main()
{
	// Create Window
	initWindow("Test Window", 1366, 768);

	// Create Vulkan Renderer instance
	if (vulkanRenderer.init(window) == EXIT_FAILURE)
	{
		return EXIT_FAILURE;
	}

	float angle = 0.0f;
	float deltaTime = 0.0f;
	float lastTime = 0.0f;

	int helicopter = vulkanRenderer.createMeshModel("Models/chopper.obj");

	// Loop until closed
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		// For Rotating
		float now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		angle += 25.0f * deltaTime;
		if (angle > 360.0f) { angle -= 360.0f; }

		// For Scaling
		float dynamic_scaling = 0.22f;

		float deltaTime2 = 0.0f, lastTime2 = 0.0f;
		float now2 = glfwGetTime();
		deltaTime2 = now2 - lastTime2;
		lastTime2 = now2;

		if (dynamic_scaling == 0.22f) { dynamic_scaling += 0.05f * deltaTime2; }
		if (dynamic_scaling > 1.2f) { dynamic_scaling = 1.2f; }
		
		glm::mat4 testMat;
		testMat = glm::rotate(glm::mat4(1.0f), glm::radians(angle * -1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		testMat = glm::rotate(testMat, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		testMat = glm::translate(testMat, glm::vec3(0.0f, 2.0f, 0.0f));
		testMat = glm::scale(testMat, glm::vec3(dynamic_scaling, dynamic_scaling, dynamic_scaling));

		vulkanRenderer.updateModel(helicopter, testMat);

		vulkanRenderer.draw();
	}

	vulkanRenderer.cleanup();

	// Destroy GLFW window and stop GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}