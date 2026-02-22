
#include "glad/glad.h"

#include "Reticle.h"


static float vertices[] =
{
	 0.05f,  0.0f,  0.0f,
	-0.05f,  0.0f,  0.0f,
	 0.0f,   0.05f, 0.0f,
	 0.0f,  -0.05f, 0.0f
};


Reticle::Reticle(Program* shaderProgram)
	: shaderProgram(shaderProgram)
{
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * 4 * sizeof(float), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


Reticle::~Reticle()
{
	glDeleteVertexArrays(1, &this->vao);
	glDeleteBuffers(1, &this->vbo);
}


Program* Reticle::getProgram()
{
	return this->shaderProgram;
}


void Reticle::draw()
{
	glUseProgram(this->shaderProgram->id);
	glBindVertexArray(this->vao);
	glDrawArrays(GL_LINES, 0, 4);
	glBindVertexArray(0);
}