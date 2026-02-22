

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
	this->model     = new LightModel(this->intensity, this->color, this->position, this->shaderProgram, this->affectedPrograms);
	this->removable = false;
}


void Light::setColor(float r, float g, float b)
{
	this->color = glm::vec3(r, g, b);
}


Model* Light::getModel()
{
	this->model->setColor(this->color);
	this->model->setPosition(this->position);
	this->model->setIntensity(this->intensity);

	return this->model;
}


Light::~Light()
{
	delete this->model;
}