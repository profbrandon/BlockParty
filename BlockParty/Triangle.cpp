

#include "Triangle.h"

#include "glm/gtc/matrix_transform.hpp"


Triangle::Triangle(const glm::vec3 v1, const glm::vec3 v2, const glm::vec3 v3)
	: v1(glm::vec3(v1.x, v1.y, v1.z)),
	  v2(glm::vec3(v2.x, v2.y, v2.z)),
	  v3(glm::vec3(v3.x, v3.y, v3.z))
{
	this->normal = glm::normalize(glm::cross(this->v3 - this->v1, this->v2 - this->v1));
}


glm::vec3 Triangle::getNormal()
{
	return this->normal;
}