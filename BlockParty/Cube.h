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

	void setSelected(bool selected) override;

	Model* getModel() override;

	~Cube();
};