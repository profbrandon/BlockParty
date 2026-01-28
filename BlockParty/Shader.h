#pragma once

class Shader
{
private:
	Shader(unsigned int id);

	static Shader* compileShader(const char* shaderSource, unsigned int shaderType);

public:
	const unsigned int id;

	static Shader* buildShader(const char* filePath, unsigned int shaderType);
};