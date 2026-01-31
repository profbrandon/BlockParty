#pragma once

#include <map>
#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Camera.h"
#include "ModelContainer.h"

struct KeyInfo
{
	double waitPress    = 0.0f;
	double waitRelease  = 0.0f;

	double lastPress    = 0.0f;
	double lastRelease  = 0.0f;

	void (*onPress)()   = nullptr;
	void (*onRelease)() = nullptr;
};


class Window
{
private:
	GLFWwindow* window;

	void(*it)() = nullptr;

	std::vector<unsigned int> keys;

	std::map<unsigned int, KeyInfo>   keyInfoMap;

public:
	Window(GLFWwindow* window);

	~Window();

	void bindLoopFunction(void (*it)());

	void enterLoop(Camera* camera, ModelContainer* models);

	void bindKeyPress(unsigned int keyCode, double wait, void (*onPress)());

	void bindKeyRelease(unsigned int keyCode, double wait, void (*onPress)());

	void bindCursorMovement(void* (onMove)(double deltaX, double deltaY));

	void bindCursorClick(void* (onClick)(double xPos, double yPos));

	void close();

	bool isClosing();

	void processInputs();

	static Window* initializeWindow(int width, int height, const char* name);
};