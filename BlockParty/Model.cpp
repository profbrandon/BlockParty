
#include "Model.h"

#include <iostream>

#include "stdlib.h"

#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"


Model::Model(
	float*        vertices,
	unsigned int  v_size,
	unsigned int* indices,
	unsigned int  i_size,
	glm::vec3     color,
	glm::vec3     position,
	Program*      shaderProgram)
	: vao(0),
	  i_size(i_size), 
	  color(color), 
	  position(position), 
	  shaderProgram(shaderProgram)
{
	// Build array (vertices + normal vectors)
	// Array dimensions should be indices * 6 (float)

	unsigned int num_indices = i_size / sizeof(unsigned int);

	unsigned int size = num_indices * 6;

	float* array = (float*) malloc(size * sizeof(float));

	if (array == nullptr)
	{
		std::cout << "Fuck C++" << std::endl;
		return;
	}

	for (int t = 0; t < num_indices; t += 3)
	{
		float* v1_ptr_x = vertices + 3 * indices[t];
		float* v1_ptr_y = v1_ptr_x + 1;
		float* v1_ptr_z = v1_ptr_x + 2;

		float* v2_ptr_x = vertices + 3 * indices[t + 1];
		float* v2_ptr_y = v2_ptr_x + 1;
		float* v2_ptr_z = v2_ptr_x + 2;

		float* v3_ptr_x = vertices + 3 * indices[t + 2];
		float* v3_ptr_y = v3_ptr_x + 1;
		float* v3_ptr_z = v3_ptr_x + 2;

		glm::vec3 v1 (*v1_ptr_x, *v1_ptr_y, *v1_ptr_z);
		glm::vec3 v2 (*v2_ptr_x, *v2_ptr_y, *v2_ptr_z);
		glm::vec3 v3 (*v3_ptr_x, *v3_ptr_y, *v3_ptr_z);

		glm::vec3 normal = glm::normalize(glm::cross(v3 - v1, v2 - v1));


		int j = 3 * 2 * t;

		array[j]     = v1.x;
		array[j + 1] = v1.y;
		array[j + 2] = v1.z;
		array[j + 3] = normal.x;
		array[j + 4] = normal.y;
		array[j + 5] = normal.z;

		array[j + 6]  = v2.x;
		array[j + 7]  = v2.y;
		array[j + 8]  = v2.z;
		array[j + 9]  = normal.x;
		array[j + 10] = normal.y;
		array[j + 11] = normal.z;

		array[j + 12] = v3.x;
		array[j + 13] = v3.y;
		array[j + 14] = v3.z;
		array[j + 15] = normal.x;
		array[j + 16] = normal.y;
		array[j + 17] = normal.z;
	}

	// Build vertex array object
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), array, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


Model::~Model()
{
	glDeleteVertexArrays(1, &this->vao);
	glDeleteBuffers(1, &this->vbo);
}


void Model::setSelected(bool selected)
{
	this->selected = selected;
}


void Model::setPosition(float x, float y, float z)
{
	this->position = glm::vec3(x, y, z);
}


unsigned int Model::getVertexArrayObject()
{
	return this->vao;
}

void Model::draw()
{
	this->shaderProgram->setBool("selected", this->selected);
	this->shaderProgram->setFloat3("objColor", this->color.r, this->color.g, this->color.b);
	this->shaderProgram->setMatrix4f("model", glm::translate(glm::mat4(1.0f), this->position));

	glUseProgram(this->shaderProgram->id);
	glBindVertexArray(this->vao);
	glDrawArrays(GL_TRIANGLES, 0, i_size / (sizeof(unsigned int)));
	glBindVertexArray(0);
}