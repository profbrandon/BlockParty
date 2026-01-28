
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define DEFAULT_WIDTH	1000
#define DEFAULT_HEIGHT	600
#define APP_NAME        "Block Party"


GLFWwindow* initializeGLFWWindow();


int main()
{
	GLFWwindow* window = initializeGLFWWindow();


	glfwTerminate();
	return EXIT_SUCCESS;
}


GLFWwindow* initializeGLFWWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window =
		glfwCreateWindow(
			DEFAULT_WIDTH,
			DEFAULT_HEIGHT,
			APP_NAME,
			NULL,			// No monitor
			NULL			// No sharing
		);

	if (window == NULL)
	{
		std::cerr << "Failed to create GLFW window." << std::endl;

		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	bool loadedCorrectly = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	
	if (!loadedCorrectly)
	{
		std::cerr << "Failed to load procedure loading function 'glfwGetProcAddress'" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	return window;
}