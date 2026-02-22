#pragma once

#include "Program.h"

class Reticle
{
private:
	unsigned int vao = 0;
	unsigned int vbo = 0;

	Program* shaderProgram;

public:
	Reticle(Program* shaderProgram);

	~Reticle();

	Program* getProgram();

	void draw();
};