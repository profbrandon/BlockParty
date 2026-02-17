#pragma once

#include "Object.h"
#include "LightModel.h"


class Light : public Object
{
private:
	float intensity;

	std::vector<Program*>& affectedPrograms;

	LightModel* model;

public:
	Light(
		int x,
		int y,
		int z,
		float r,
		float g,
		float b,
		float intensity,
		Program* shaderProgram,
		std::vector<Program*>& affectedPrograms);


	void setColor(float r, float g, float b);

	Model* getModel() override;

	~Light();
};