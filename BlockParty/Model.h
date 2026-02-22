#pragma once

#include "glm/vec3.hpp"

#include "Program.h"
#include "Triangle.h"

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
	std::vector<Triangle*> triangles;

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

	glm::mat4 getModelMatrix();

	std::pair<Triangle*, float>* rayIntersection(glm::vec3 rayStart, glm::vec3 rayDir);
	
	virtual void draw();
};