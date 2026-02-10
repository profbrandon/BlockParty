
#include "Camera.h"

#include <iostream>

#include "glm/vec4.hpp"
#include "glm/gtc/matrix_transform.hpp"


Camera::Camera(float minPitch, float maxPitch)
	: minPitch(minPitch), maxPitch(maxPitch)
{

}


void Camera::computeVectors()
{
	glm::mat4 yawMatrix   = glm::rotate(glm::mat4(1.0f), this->yaw,   this->up);
	glm::mat4 pitchMatrix = glm::rotate(glm::mat4(1.0f), this->pitch, this->initRight);

	this->right = yawMatrix * glm::vec4(this->initRight, 1.0f);
	this->front = yawMatrix * pitchMatrix * glm::vec4(this->initFront, 1.0f);
}


void Camera::addPitch(float radians)
{
	this->pitch -= radians;

	if (this->pitch > this->maxPitch)
		this->pitch = this->maxPitch;

	if (this->pitch < this->minPitch)
		this->pitch = this->minPitch;

	this->computeVectors();
}


void Camera::addYaw(float radians)
{
	this->yaw -= radians;
	this->computeVectors();
}


void Camera::strafe(float amount)
{
	this->position += this->right * amount;
}


void Camera::approach(float amount)
{
	glm::mat4 yawMatrix = glm::rotate(glm::mat4(1.0f), this->yaw, this->up);

	this->position += yawMatrix * glm::vec4(this->initFront, 1.0f) * amount;
}


void Camera::setPosition(float x, float y, float z)
{
	this->position = glm::vec3(x, y, z);
}

glm::vec3 Camera::getPosition()
{
	return this->position;
}


glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(this->position, this->position + this->front, this->up);
}