
#include "CubeModel.h"


float vertices[] =
{
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f,  0.5f,

	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f
};

unsigned int indices[] =
{
	1, 0, 3,
	1, 5, 0,
	1, 3, 5,

	2, 3, 0,
	2, 6, 3,
	2, 0, 6,

	4, 0, 5,
	4, 5, 6,
	4, 6, 0,

	7, 3, 6,
	7, 6, 5,
	7, 5, 3
};


CubeModel::CubeModel(glm::vec3 color, glm::vec3 position, Program* shaderProgram) 
	: Model(
		vertices, 
		sizeof(vertices), 
		indices, 
		sizeof(indices),
		color,
		position,
		shaderProgram)
{

}