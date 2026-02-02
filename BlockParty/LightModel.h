#pragma once

#include "CubeModel.h"

class LightModel : public CubeModel
{
private:
	float intensity;
	std::vector<Program*>& affectedPrograms;

public:
	LightModel(
		float intensity, 
		glm::vec3 color, 
		glm::vec3 position,
		Program* shaderProgram,
		std::vector<Program*>& affectedPrograms);

	void draw() override;
};