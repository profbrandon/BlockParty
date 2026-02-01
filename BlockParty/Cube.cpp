

#include "Cube.h"
#include "CubeModel.h"

Cube::Cube(int x, int y, int z, Program* shaderProgram)
	: Object(glm::vec3(x, y, z), shaderProgram)
{

}

Model* Cube::getModel()
{
	return new CubeModel(this->position, this->shaderProgram);
}