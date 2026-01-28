
#include "Camera.h"

#include "glm/vec4.hpp"
#include "glm/gtc/matrix_transform.hpp"


Camera::Camera(glm::vec3 position, float minPitch, float maxPitch)
	: position(position), minPitch(minPitch), maxPitch(maxPitch)
{

}


void Camera::addPitch(float radians)
{
	this->pitch += radians;

	if (this->pitch > maxPitch)
		this->pitch = maxPitch;

	if (this->pitch < minPitch)
		this->pitch = minPitch;

	glm::mat4 yawMatrix   = glm::rotate(glm::mat4(1.0f), this->yaw,   this->up);
	glm::mat4 pitchMatrix = glm::rotate(glm::mat4(1.0f), this->pitch, this->right);

	this->front = pitchMatrix * yawMatrix * glm::vec4(this->initFront, 1.0f);
}


void Camera::addYaw(float radians)
{
	this->yaw += radians;

	glm::mat4 yawMatrix = glm::rotate(glm::mat4(1.0f), this->yaw, this->up);

	this->right = yawMatrix * glm::vec4(this->initRight, 1.0f);
}


glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(this->position, this->position + this->front, this->up);
}