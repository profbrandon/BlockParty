#pragma once

#include "glm/vec3.hpp"

#include "Model.h"
#include "Program.h"


class Object
{
protected:
	glm::vec3 color;
	glm::vec3 position;

	Program* shaderProgram;

	Object(glm::vec3 color, glm::vec3 position, Program* shaderProgram);

public:
	unsigned int id;

	glm::vec3 getPosition();

	void setPosition(float x, float y, float z);

	Program* getProgram();

	virtual Model* getModel() = 0;
};