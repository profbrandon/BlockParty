
#include "LightModel.h"


LightModel::LightModel(
	float intensity,
	glm::vec3 color,
	glm::vec3 position,
	Program* shaderProgram,
	std::vector<Program*>& affectedPrograms)

	: CubeModel(color, position, shaderProgram),
	  intensity(intensity),
	  affectedPrograms(affectedPrograms)
{

}


void LightModel::setColor(glm::vec3 color)
{
	this->color = color;
}


void LightModel::setPosition(glm::vec3 position)
{
	this->position = position;
}


void LightModel::setIntensity(float intensity)
{
	this->intensity = intensity;
}


void LightModel::draw()
{
	this->shaderProgram->setFloat3("lightColor", this->color.r, this->color.g, this->color.b);
	this->shaderProgram->setFloat("intensity", this->intensity);

	for (Program* program : this->affectedPrograms)
	{
		program->setFloat3("lightPos", this->position.x, this->position.y, this->position.z);
		program->setFloat3("lightColor", this->color.r, this->color.g, this->color.b);
		program->setFloat("intensity", this->intensity);
	}

	this->Model::draw();
}