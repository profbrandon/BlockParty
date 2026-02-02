

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

}

Model* Cube::getModel()
{
	return new CubeModel(this->color, this->position, this->shaderProgram);
}