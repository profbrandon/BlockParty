

#include "Light.h"
#include "LightModel.h"


Light::Light(
	int x,
	int y,
	int z,
	float r,
	float g,
	float b,
	float intensity,
	Program* shaderProgram,
	std::vector<Program*>& affectedPrograms)
	: Object(glm::vec3(r, g, b), glm::vec3(x, y, z), shaderProgram),
	  intensity(intensity),
	  affectedPrograms(affectedPrograms)
{

}


Model* Light::getModel()
{
	return new LightModel(
		this->intensity, 
		this->color, 
		this->position, 
		this->shaderProgram, 
		this->affectedPrograms);
}