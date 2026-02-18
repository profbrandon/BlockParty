#pragma once

#include "glm/vec3.hpp"

#include "Model.h"
#include "Program.h"


class Object
{
protected:
	bool selected = false;

	glm::vec3 color;
	glm::vec3 position;

	Program* shaderProgram;

	Object(glm::vec3 color, glm::vec3 position, Program* shaderProgram);

public:
	unsigned int id;

	glm::vec3 getPosition();

	bool isSelected();

	void setPosition(float x, float y, float z);

	virtual void setSelected(bool selected);

	Program* getProgram();

	virtual Model* getModel() = 0;
};