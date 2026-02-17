#pragma once

#include "Object.h"
#include "CubeModel.h"


class Cube : public Object
{
private:
	CubeModel* model;

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

	~Cube();
};