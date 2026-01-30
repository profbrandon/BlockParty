
#include <iostream>

#include "Window.h"
#include "Shader.h"

#define DEFAULT_WIDTH	1000
#define DEFAULT_HEIGHT	600
#define APP_NAME        "Block Party"


void iteration();

int main()
{
	Window* window = Window::initializeWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, APP_NAME);

	if (window == nullptr) 
		return EXIT_FAILURE; 

	Shader* vertexShader   = Shader::buildShader("vertex.glsl", GL_VERTEX_SHADER);
	Shader* fragmentShader = Shader::buildShader("fragment.glsl", GL_FRAGMENT_SHADER);

	if (vertexShader == NULL || fragmentShader == NULL)
	{
		delete window;
		delete vertexShader;
		delete fragmentShader;
		return EXIT_FAILURE;
	}

	window->bindLoopFunction(iteration);
	window->enterLoop();

	delete window;
	delete vertexShader;
	delete fragmentShader;
	return EXIT_SUCCESS;
}


void iteration()
{

}