#pragma once

#include "Object.h"


class Cube : public Object
{
public:
	Cube(glm::vec3 position, unsigned int shaderProgram);

	Model* getModel() override;
};