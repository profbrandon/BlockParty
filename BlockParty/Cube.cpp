

#include "Cube.h"
#include "CubeModel.h"

Cube::Cube(glm::vec3 position, unsigned int shaderProgram)
	: Object(position, shaderProgram)
{

}

Model* Cube::getModel()
{
	return new CubeModel(this->shaderProgram);
}