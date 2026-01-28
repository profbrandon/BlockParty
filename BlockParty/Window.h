#pragma once

#include <map>
#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

struct KeyInfo
{
	double wait;

	double lastPress;
	double lastRelease;
};


class Window
{
private:
	GLFWwindow* window;

	void(*it)() = nullptr;

	std::vector<unsigned int> keys;

	std::map<unsigned int, KeyInfo>   keyInfoMap;
	std::map<unsigned int, void(*)()> keyPressMap;

public:
	Window(GLFWwindow* window);

	~Window();

	void bindLoopFunction(void (*it)());

	void enterLoop();

	void bindKeyPress(unsigned int keyCode, double wait, void (*onPress)());

	void bindKeyRelease(unsigned int keyCode, double wait, void (*onPress)());

	void bindCursorMovement(void* (onMove)(double deltaX, double deltaY));

	void bindCursorClick(void* (onClick)(double xPos, double yPos));

	void close();

	bool isClosing();

	void processInputs();

	static Window* initializeWindow(int width, int height, const char* name);
};