#pragma once

#include "glm/vec3.hpp"

#include "Program.h"

class Model
{
private:
	unsigned int vao;
	unsigned int i_size;

	glm::vec3    color;
	glm::vec3    position;

	Program*     shaderProgram;

public:
	Model(
		float*        vertices,
		unsigned int  v_size,
		unsigned int* indices,
		unsigned int  i_size,
		glm::vec3     color,
		glm::vec3     position,
		Program*      shaderProgram
	);

	unsigned int getVertexArrayObject();
	
	void draw();
};