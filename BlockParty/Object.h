#pragma once

#include "glm/vec3.hpp"

#include "Model.h"


class Object
{
protected:
	glm::vec3 position;

	unsigned int shaderProgram;

	Object(glm::vec3 position, unsigned int shaderProgram);

public:
	unsigned int id;

	virtual Model* getModel() = 0;
};