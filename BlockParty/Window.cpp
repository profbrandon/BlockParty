
#include "Window.h"

#include <iostream>



void doNothing()
{

}


Window::Window(GLFWwindow* window)
	: window(window)
{

}


void Window::bindLoopFunction(void (*it)())
{
	this->it = it;
}


void Window::enterLoop(Camera* camera, ModelContainer* models)
{
	if (this->it == nullptr) return;

	while (!this->isClosing())
	{
		this->processInputs();
		
		this->it();

		glm::mat4 view = camera->getViewMatrix();

		models->processModels([](const Model* model) {
				
			});

		glfwSwapBuffers(this->window);
		glfwPollEvents();
	}
}


void Window::bindKeyPress(unsigned int keyCode, double wait, void (*onPress)())
{
	this->keys.push_back(keyCode);

	const double currentTime = glfwGetTime();

	KeyInfo* keyInfo = &this->keyInfoMap[keyCode];

	keyInfo->waitPress   = wait;
	keyInfo->onPress     = onPress;
}


void Window::bindKeyRelease(unsigned int keyCode, double wait, void (*onRelease)(void))
{
	this->keys.push_back(keyCode);

	const double currentTime = glfwGetTime();

	KeyInfo* keyInfo = &this->keyInfoMap[keyCode];

	keyInfo->waitRelease = wait;
	keyInfo->onRelease   = onRelease;
}


void Window::close()
{
	glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}


bool Window::isClosing()
{
	return glfwWindowShouldClose(this->window);
}


void Window::processInputs()
{
	double currentTime = glfwGetTime();

	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		this->close();
		return;
	}

	for (unsigned int keyCode : this->keys)
	{
		int keyStatus = glfwGetKey(this->window, keyCode);

		KeyInfo* keyInfo = &this->keyInfoMap[keyCode];

		switch (keyStatus)
		{
		case GLFW_PRESS:
			if (keyInfo->onPress == nullptr)
				break;

			if (currentTime - keyInfo->lastPress > keyInfo->waitPress)
			{
				keyInfo->lastPress = currentTime;
				keyInfo->onPress();
			}
			break;

		case GLFW_RELEASE:
			if (keyInfo->onRelease == nullptr)
				break;

			if (currentTime - keyInfo->lastRelease > keyInfo->waitRelease)
			{
				keyInfo->lastRelease = currentTime;
				keyInfo->onRelease();
			}
		}
	}
}


Window* Window::initializeWindow(int width, int height, const char* name)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window =
		glfwCreateWindow(
			width,
			height,
			name,
			NULL,			// No monitor
			NULL			// No sharing
		);

	if (window == NULL)
	{
		std::cerr << "Failed to create GLFW window." << std::endl;
		
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);

	bool loadedCorrectly = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	if (!loadedCorrectly)
	{
		std::cerr << "Failed to load procedure loading function 'glfwGetProcAddress'" << std::endl;

		glfwTerminate();
		return nullptr;
	}

	return new Window(window);
}


Window::~Window()
{
	std::cout << "Closing window..." << std::endl;

	this->close();
	glfwTerminate();
}