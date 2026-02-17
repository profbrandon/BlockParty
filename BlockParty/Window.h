#pragma once

#include <map>
#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Camera.h"
#include "ObjectContainer.h"

struct KeyInfo
{
	bool   newPress     = true;

	double waitPress    = 0.0f;
	double waitRelease  = 0.0f;

	double lastPress    = 0.0f;
	double lastRelease  = 0.0f;

	void (*onPress)(double deltaT)   = nullptr;
	void (*onRelease)(double deltaT) = nullptr;
};


class Window
{
private:
	GLFWwindow* window;

	void(*it)(double deltaT) = nullptr;

	std::vector<unsigned int> keys;

	std::map<unsigned int, KeyInfo> keyInfoMap;

	bool cursorMode = false;


	Window(GLFWwindow* window, int width, int height);

public:
	~Window();

	void bindLoopFunction(void (*it)(double deltaT));

	void enterLoop(Camera* camera, ObjectContainer* models);

	void bindKeyPress(unsigned int keyCode, double wait, void (*onPress)(double deltaT));

	void bindKeyRelease(unsigned int keyCode, double wait, void (*onRelease)(double deltaT));

	void bindCursorMovement(void (*onMove)(double xPos, double yPos));

	void bindCursorClick(void (*onClick)(double xPos, double yPos));

	void setCursorMode(bool onOrOff);

	bool getCursorMode();

	void close();

	bool isClosing();

	void processInputs();

	static Window* initializeWindow(int width, int height, const char* name);
};