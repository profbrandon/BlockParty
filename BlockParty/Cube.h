#pragma once

#include "Object.h"


class Cube : public Object
{
public:
	Cube(
		int x, 
		int y, 
		int z,
		float r, 
		float g, 
		float b,
		Program* shaderProgram);

	Model* getModel() override;
};