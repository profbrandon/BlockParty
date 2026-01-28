
#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "glad/glad.h"


Shader::Shader(unsigned int id) : id(id) 
{ 

};


Shader* Shader::compileShader(const char* shaderSource, unsigned int shaderType)
{
	unsigned int shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &shaderSource, NULL);
	glCompileShader(shaderId);

	int success;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);

		std::cout
			<< "Failed to compile shader:" << std::endl
			<< shaderSource                << std::endl << std::endl
			<< "Reason:"                   << std::endl
			<< infoLog                     << std::endl;

		return nullptr;
	}

	return new Shader(shaderId);
}


Shader* Shader::buildShader(const char* filePath, unsigned int shaderType)
{
	std::fstream file(filePath, std::fstream::in);

	if (!file.is_open())
	{
		std::cerr << "Failed to open shader file at '" << filePath << "'." << std::endl;
		return nullptr;
	}

	std::ostringstream s;
	s << file.rdbuf();

	return compileShader(s.str().c_str(), shaderType);
}