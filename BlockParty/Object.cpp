
#include "Object.h"


Object::Object(
	glm::vec3 color,
	glm::vec3 position, 
	Program* shaderProgram)
	: color(color),
	  position(position),
	  shaderProgram(shaderProgram)
{
	static unsigned int max_id = 0;
	this->id = max_id;
	++max_id;
}


bool Object::isSelected()
{
	return this->selected;
}


glm::vec3 Object::getPosition()
{
	return this->position;
}


void Object::setSelected(bool selected)
{
	this->selected = selected;
}


void Object::setPosition(float x, float y, float z)
{
	this->position = glm::vec3(x, y, z);
}


Program* Object::getProgram()
{
	return this->shaderProgram;
}