#pragma once

#include "Model.h"
#include "Program.h"

class CubeModel : public Model
{
public:
	CubeModel(glm::vec3 position, Program* shaderProgram);
};