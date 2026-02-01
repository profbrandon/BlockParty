#pragma once

#include "Object.h"


class Cube : public Object
{
public:
	Cube(int x, int y, int z, Program* shaderProgram);

	Model* getModel() override;
};