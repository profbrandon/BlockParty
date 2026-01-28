
#include "Model.h"


#include "stdlib.h"

#include "glad/glad.h"


Model::Model(
	float*       vertices,
	unsigned int v_size,
	float*       indices,
	unsigned int i_size,
	unsigned int shaderProgram)
	: i_size(i_size), shaderProgram(shaderProgram)
{
	// Build vertex array object
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, v_size, vertices, GL_STATIC_DRAW);

	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_size, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int Model::getVertexArrayObject()
{
	return this->vao;
}

void Model::draw()
{
	glUseProgram(this->shaderProgram);
	glBindVertexArray(this->vao);
	glDrawElements(GL_TRIANGLES, (int)(this->i_size / sizeof(unsigned int)), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}