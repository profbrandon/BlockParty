#pragma once

#include "glm/vec3.hpp"

#include "Program.h"

class Model
{
protected:
	bool selected = false;

	unsigned int vao;
	unsigned int vbo;
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

	~Model();

	void setPosition(float x, float y, float z);

	virtual void setSelected(bool selected);

	unsigned int getVertexArrayObject();
	
	virtual void draw();
};