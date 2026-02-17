

#include "Cube.h"
#include "CubeModel.h"

Cube::Cube(
	int x,
	int y,
	int z,
	float r,
	float g,
	float b,
	Program* shaderProgram)
	: Object(glm::vec3(r, g, b), glm::vec3(x, y, z), shaderProgram)
{
	this->model = new CubeModel(this->color, this->position, this->shaderProgram);
}

Model* Cube::getModel()
{
	glm::vec3 pos = this->position;
	this->model->setPosition(pos.x, pos.y, pos.z);
	return this->model;
}

Cube::~Cube()
{
	delete this->model;
}