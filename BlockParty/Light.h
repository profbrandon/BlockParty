#pragma once

#include "Object.h"


class Light : public Object
{
private:
	float intensity;

	std::vector<Program*>& affectedPrograms;

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

	Model* getModel() override;
};