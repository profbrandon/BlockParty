#pragma once

#include "glm/vec3.hpp"

#include "Model.h"
#include "Program.h"


class Object
{
protected:
	bool selected  = false;
	bool removable = true;

	glm::vec3 color;
	glm::vec3 position;

	Program* shaderProgram;

	Object(glm::vec3 color, glm::vec3 position, Program* shaderProgram);

public:
	unsigned int id;

	glm::vec3 getPosition();

	bool isSelected();

	bool isRemovable();

	void setPosition(float x, float y, float z);

	virtual void setSelected(bool selected);

	virtual void setRemovable(bool removable);

	Program* getProgram();

	virtual Model* getModel() = 0;
};