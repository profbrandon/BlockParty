#pragma once

#include "glm/vec3.hpp"

#include "Model.h"
#include "Program.h"


class Object
{
protected:
	glm::vec3 position;

	Program* shaderProgram;

	Object(glm::vec3 position, Program* shaderProgram);

public:
	unsigned int id;

	glm::vec3 getPosition();

	Program* getProgram();

	virtual Model* getModel() = 0;
};