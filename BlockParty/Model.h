#pragma once


class Model
{
private:
	unsigned int vao;
	unsigned int shaderProgram;

	unsigned int i_size;

public:
	Model(
		float*       vertices,
		unsigned int v_size,
		float*       indices,
		unsigned int i_size,
		unsigned int shaderProgram
	);

	unsigned int getVertexArrayObject();
	
	void draw();
};