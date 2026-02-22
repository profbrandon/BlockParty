
#include "Window.h"

#include <iostream>

#include "glm/gtc/type_ptr.hpp"



void defaultCursorCallback(double x, double y)
{

}


void defaultClickCallback(int button, double x, double y)
{

}


static Window* instance = nullptr;

static double mousePosX = 0;
static double mousePosY = 0;

static int window_width  = 0;
static int window_height = 0;

static void (*cursorCallback)(double x, double y) = defaultCursorCallback;

static void (*clickCallback)(int button, double x, double y) = defaultClickCallback;


void frameBufferResizeCallback(GLFWwindow* window, int width, int height)
{
	window_width  = width;
	window_height = height;
	glViewport(0, 0, width, height);
}


void cursorPositionCallback(GLFWwindow* window, double x, double y)
{
	mousePosX = x;
	mousePosY = y;

	cursorCallback(x, y);
}


void cursorClickCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
		clickCallback(button, mousePosX, mousePosY);
}


void doNothing()
{

}






Window::Window(GLFWwindow* window, int width, int height)
	: window(window)
{
	window_width  = width;
	window_height = height;

	this->setCursorMode(false);
	glfwSetCursorPosCallback(window, cursorPositionCallback);
	glfwSetMouseButtonCallback(window, cursorClickCallback);
	glfwSetFramebufferSizeCallback(window, frameBufferResizeCallback);
}


void Window::bindLoopFunction(void (*it)(double deltaT))
{
	this->it = it;
}


void Window::enterLoop(Camera* camera, ObjectContainer* container)
{
	static double lastTime = glfwGetTime();

	if (this->it == nullptr) return;

	double deltaT = 0;

	glEnable(GL_DEPTH_TEST);

	while (!this->isClosing())
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		this->processInputs();
		
		this->it(deltaT);

		glm::mat4 viewMatrix = camera->getViewMatrix();
		glm::mat4 projMatrix = glm::perspective(glm::radians(45.0f), (float)window_width / window_height, 0.1f, 100.0f);


		auto objects = container->getObjects();

		for (Object* object : objects)
		{
			object->getProgram()->setMatrix4f("view", viewMatrix);
			object->getProgram()->setMatrix4f("proj", projMatrix);

			object->getModel()->draw();
		}


		if (this->reticle != nullptr) {
			this->reticle->getProgram()->use();
			this->reticle->getProgram()->setMatrix4f("proj", glm::scale(glm::mat4(1.0f), glm::vec3((float) window_height / window_width, 1.0f, 0.0f)));
			this->reticle->draw();
		}


		glfwSwapBuffers(this->window);
		glfwPollEvents();

		double currentTime = glfwGetTime();

		deltaT   = currentTime - lastTime;
		lastTime = currentTime;
	}
}


void Window::bindKeyPress(unsigned int keyCode, double wait, void (*onPress)(double deltaT))
{
	this->keys.push_back(keyCode);

	const double currentTime = glfwGetTime();

	KeyInfo* keyInfo = &this->keyInfoMap[keyCode];

	keyInfo->waitPress   = wait;
	keyInfo->onPress     = onPress;
}


void Window::bindKeyRelease(unsigned int keyCode, double wait, void (*onRelease)(double deltaT))
{
	this->keys.push_back(keyCode);

	const double currentTime = glfwGetTime();

	KeyInfo* keyInfo = &this->keyInfoMap[keyCode];

	keyInfo->waitRelease = wait;
	keyInfo->onRelease   = onRelease;
}


void Window::bindCursorMovement(void (*onMove)(double xPos, double yPos))
{
	cursorCallback = (onMove == nullptr) ? defaultCursorCallback : onMove;
}


void Window::bindCursorClick(void (*onClick)(int button, double xPos, double yPos))
{
	clickCallback = (onClick == nullptr) ? defaultClickCallback : onClick;
}


void Window::setReticle(Reticle* reticle)
{
	this->reticle = reticle;
}


void Window::setCursorMode(bool onOrOff)
{
	this->cursorMode = onOrOff;
	glfwSetInputMode(
		window, 
		GLFW_CURSOR, 
		this->cursorMode 
			? GLFW_CURSOR_NORMAL 
		    : GLFW_CURSOR_DISABLED);
}


bool Window::getCursorMode()
{
	return this->cursorMode;
}


void Window::close()
{
	this->setCursorMode(true);
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

		double deltaT = 0.0f;

		switch (keyStatus)
		{
		case GLFW_PRESS:
			if (keyInfo->onPress == nullptr)
				break;

			deltaT = currentTime - keyInfo->lastPress;

			if (deltaT > keyInfo->waitPress)
			{
				keyInfo->lastPress = currentTime;
				keyInfo->onPress(keyInfo->newPress ? keyInfo->waitPress : deltaT);
			}

			keyInfo->newPress = false;
			break;

		case GLFW_RELEASE:
			keyInfo->newPress = true;

			if (keyInfo->onRelease == nullptr)
				break;

			deltaT = currentTime - keyInfo->lastRelease;

			if (deltaT > keyInfo->waitRelease)
			{
				keyInfo->lastRelease = currentTime;
				keyInfo->onRelease(deltaT);
			}
		}
	}
}


Window* Window::initializeWindow(int width, int height, const char* name)
{
	if (instance != nullptr) return instance;

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

	instance = new Window(window, width, height);
	
	return instance;
}


Window::~Window()
{
	std::cout << "Closing window..." << std::endl;

	this->close();
	glfwTerminate();
}