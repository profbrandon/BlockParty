
#include <iostream>

#include "Window.h"
#include "Shader.h"
#include "Camera.h"
#include "World.h"

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

	Camera* camera = new Camera(6.28f / 3.0f, - 6.28f / 3.0f);
	World*  world  = new World();

	window->bindLoopFunction(iteration);
	window->enterLoop(camera, (ModelContainer*) world);

	delete window;
	delete vertexShader;
	delete fragmentShader;
	return EXIT_SUCCESS;
}


void iteration()
{

}