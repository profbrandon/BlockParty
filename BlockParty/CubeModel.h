#pragma once

#include "Model.h"

class CubeModel : public Model
{
public:
	CubeModel(glm::vec3 color, glm::vec3 position, Program* shaderProgram);
};