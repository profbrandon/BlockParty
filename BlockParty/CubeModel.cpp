
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
	3, 0, 1,
	0, 1, 5,
	1, 5, 3,

	0, 3, 2,
	3, 2, 6,
	2, 6, 0,

	0, 5, 4,
	5, 4, 6,
	4, 6, 0,

	3, 6, 7,
	6, 7, 5,
	7, 5, 3
};


CubeModel::CubeModel(unsigned int shaderProgram) 
	: Model(
		vertices, 
		sizeof(vertices), 
		indices, 
		sizeof(indices), 
		shaderProgram)
{

}