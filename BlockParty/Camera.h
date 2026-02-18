#pragma once

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

class Camera
{
private:
	const glm::vec3 up        = glm::vec3(0.0f, 1.0f,  0.0f);
	const glm::vec3 initFront = glm::vec3(0.0f, 0.0f, -1.0f);
	const glm::vec3 initRight = glm::vec3(1.0f, 0.0f,  0.0f);

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 front    = initFront;
	glm::vec3 right    = initRight;

	const float minPitch;
	const float maxPitch;

	float pitch = 0.0f;
	float yaw   = 0.0f;

	void computeVectors();

public:
	Camera(float minPitch, float maxPitch);

	void addPitch(float radians);
	void addYaw(float radians);

	void strafe(float amount);
	void approach(float amount);

	void setPosition(float x, float y, float z);
	glm::vec3 getPosition();
	glm::vec3 getFront();

	glm::mat4 getViewMatrix();
};