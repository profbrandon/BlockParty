#pragma once

#include <vector>

#include "glm/vec3.hpp"

class Triangle
{
private:
	glm::vec3 normal;

public:
	const glm::vec3 v1;
	const glm::vec3 v2;
	const glm::vec3 v3;

	Triangle(const glm::vec3 v1, const glm::vec3 v2, const glm::vec3 v3);

	glm::vec3 getNormal();
};