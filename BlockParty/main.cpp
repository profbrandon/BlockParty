
#include <iostream>

#include "Window.h"
#include "Camera.h"
#include "World.h"
#include "Light.h"
#include "Cube.h"

#include "Shader.h"
#include "Program.h"

#define DEFAULT_WIDTH	1000
#define DEFAULT_HEIGHT	600
#define APP_NAME        "Block Party"

#define MAX_PITCH       (3.14f / 3.0f)
#define MIN_PITCH       (- MAX_PITCH)
#define SENSITIVITY     0.001f
#define APPROACH_SPEED  10.0
#define STRAFE_SPEED    5.0


Window* window = nullptr;
Light*  light1 = nullptr;
Camera* camera = new Camera(MIN_PITCH, MAX_PITCH);
World*  world  = new World();

void w_press(double deltaT);
void a_press(double deltaT);
void s_press(double deltaT);
void d_press(double deltaT);
void x_press(double deltaT);

void cursorPositionCallback(double x, double y);

void iteration(double deltaT);

int main()
{
	window = Window::initializeWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, APP_NAME);

	if (window == nullptr) 
		return EXIT_FAILURE; 

	Shader* vertexShader    = Shader::buildShader("vertex.glsl",     GL_VERTEX_SHADER);
	Shader* cubeFragShader  = Shader::buildShader("cube-frag.glsl",  GL_FRAGMENT_SHADER);
	Shader* lightFragShader = Shader::buildShader("light-frag.glsl", GL_FRAGMENT_SHADER);

	if (vertexShader == NULL || cubeFragShader == NULL || lightFragShader == NULL)
	{
		delete window;
		delete vertexShader;
		delete cubeFragShader;
		delete lightFragShader;
		delete world;
		delete camera;
		return EXIT_FAILURE;
	}

	std::vector<Shader*> cubeShaders{ vertexShader, cubeFragShader };
	std::vector<Shader*> lightShaders{ vertexShader, lightFragShader };

	Program* cubeProgram = Program::buildProgram(cubeShaders);
	Program* lightProgram = Program::buildProgram(lightShaders);

	if (cubeProgram == NULL || lightProgram == NULL)
	{
		delete window;
		delete vertexShader;
		delete cubeFragShader;
		delete lightFragShader;
		delete cubeProgram;
		delete lightProgram;
		delete world;
		delete camera;
		return EXIT_FAILURE;
	}

	std::vector<Program*> lightAffectedPrograms{ cubeProgram };

	light1 = new Light( 0,  3,  0,  1.0f, 1.0f, 1.0f, 1.0f, lightProgram, lightAffectedPrograms);

	Cube* cube1 = new Cube( 3,  0, -3, 1.0f, 0.0f, 0.0f, cubeProgram);
	Cube* cube2 = new Cube(-3,  0, -3, 0.0f, 1.0f, 0.0f, cubeProgram);
	Cube* cube3 = new Cube( 3,  0,  3, 0.0f, 0.0f, 1.0f, cubeProgram);
	Cube* cube4 = new Cube(-3,  0,  3, 1.0f, 1.0f, 1.0f, cubeProgram);

	world->addObject(light1);
	world->addObject(cube1);
	world->addObject(cube2);
	world->addObject(cube3);
	world->addObject(cube4);

	world->setCamera(camera);

	window->bindKeyPress('W', 0.02f, w_press);
	window->bindKeyPress('A', 0.02f, a_press);
	window->bindKeyPress('S', 0.02f, s_press);
	window->bindKeyPress('D', 0.02f, d_press);
	window->bindKeyPress('X', 0.2f,  x_press);

	window->bindCursorMovement(cursorPositionCallback);
	window->bindLoopFunction(iteration);

	camera->setPosition(0, 1, 1);
	
	window->enterLoop(camera, (ObjectContainer*) world);
	
	delete window;
	delete vertexShader;
	delete cubeFragShader;
	delete lightFragShader;
	delete cubeProgram;
	delete lightProgram;
	delete world;
	delete camera;
	return EXIT_SUCCESS;
}


void w_press(double deltaT)
{
	camera->approach(APPROACH_SPEED * deltaT);
}


void s_press(double deltaT)
{
	camera->approach(-APPROACH_SPEED * deltaT);
}


void a_press(double deltaT)
{
	camera->strafe(-STRAFE_SPEED * deltaT);
}


void d_press(double deltaT)
{
	camera->strafe(STRAFE_SPEED * deltaT);
}


void x_press(double deltaT)
{
	if (window == nullptr)
		return;
	else
		window->setCursorMode(!window->getCursorMode());
}


void cursorPositionCallback(double x, double y)
{
	static bool is_first = true;
	static double lastX  = 0;
	static double lastY  = 0;

	if (is_first)
	{
		is_first = false;
		lastX    = x;
		lastY    = y;
		return;
	}

	camera->addPitch(SENSITIVITY * (y - lastY));
	camera->addYaw(SENSITIVITY * (x - lastX));

	lastX = x;
	lastY = y;
	return;
}


float yuh(float t, float s, float f, float w, float pos)
{
	return w * sin(f * (t + pos * s)) + (1.0f - w);
}


void iteration(double deltaT)
{
	static double t = 0.0f;
	static double s = 2.0f * 3.141592f / 3.0f;
	static double f = 10.0f;
	static double w = 0.2f;

	t += deltaT;

	light1->setColor(yuh(t,s,f,w,0.0f), yuh(t,s,f,w,1.0f), yuh(t,s,f,w,2.0f));
	light1->setPosition(2 * sin(2 * t), 3.0f, 2 * cos(2 * t));
}