#pragma once

#include <string>
#include <vector>

#include "glm/mat4x4.hpp"

#include "Shader.h"


class Program
{
private:
	Program(unsigned int id);

public:
	const unsigned int id;

	void use();

	void setBool(const std::string& name, bool value);

	void setInt(const std::string& name, int value);

	void setFloat(const std::string& name, float value);

	void setFloat2(const std::string& name, float value1, float value2);

	void setFloat3(const std::string& name, float value1, float value2, float value3);

	void setFloat4(const std::string& name, float vlaue1, float value2, float value3, float value4);

	void setMatrix4f(const std::string& name, glm::mat4 matrix);

	static Program* buildProgram(std::vector<Shader*> shaders);
};