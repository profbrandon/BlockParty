
#include "Object.h"


Object::Object(glm::vec3 position, unsigned int shaderProgram)
	: shaderProgram(shaderProgram), position(position)
{
	static unsigned int max_id = 0;
	this->id = max_id;
	++max_id;
}