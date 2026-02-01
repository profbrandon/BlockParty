
#include "Program.h"

#include <iostream>

#include "glm/gtc/type_ptr.hpp"
#include "glad/glad.h"


Program::Program(unsigned int id)
	: id(id)
{

}


void Program::use()
{
	glUseProgram(this->id);
}


void Program::setBool(const std::string& name, bool value)
{
	use();
	glUniform1i(glGetUniformLocation(this->id, name.c_str()), (int)value);
}


void Program::setInt(const std::string& name, int value)
{
	use();
	glUniform1i(glGetUniformLocation(this->id, name.c_str()), value);
}


void Program::setFloat(const std::string& name, float value)
{
	use();
	glUniform1f(glGetUniformLocation(this->id, name.c_str()), value);
}


void Program::setFloat2(const std::string& name, float value1, float value2)
{
	use();
	glUniform2f(glGetUniformLocation(this->id, name.c_str()), value1, value2);
}


void Program::setFloat3(const std::string& name, float value1, float value2, float value3)
{
	use();
	glUniform3f(glGetUniformLocation(this->id, name.c_str()), value1, value2, value3);
}


void Program::setFloat4(const std::string& name, float value1, float value2, float value3, float value4)
{
	use();
	glUniform4f(glGetUniformLocation(this->id, name.c_str()), value1, value2, value3, value4);
}


void Program::setMatrix4f(const std::string& name, glm::mat4 matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}


Program* Program::buildProgram(std::vector<Shader*> shaders)
{
	unsigned int programId = glCreateProgram();
	
	for (Shader* shader : shaders)
		glAttachShader(programId, shader->id);

	glLinkProgram(programId);

	int success;
	glGetProgramiv(programId, GL_LINK_STATUS, &success);

	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(programId, 512, NULL, infoLog);

		std::cerr
			<< "Failed to link shader program." << std::endl
			<< infoLog << std::endl;

		return nullptr;
	}

	return new Program(programId);
}