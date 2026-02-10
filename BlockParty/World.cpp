

#include "World.h"

#include <algorithm>


void World::addObject(Object* object)
{
	this->objects.push_back(object);

	if (this->camera != nullptr)
	{
		glm::vec3 cameraPos = this->camera->getPosition();
		object->getProgram()->setFloat3("viewPos", cameraPos.x, cameraPos.y, cameraPos.z);
	}
}


void World::setCamera(Camera* camera)
{
	this->camera = camera;
}


void World::removeObject(unsigned int id)
{
	std::remove_if(
		this->objects.begin(), 
		this->objects.end(), 
		[id](auto ptr) { return ptr->id == id; });
}


std::vector<Object*>& World::getObjects()
{
	glm::vec3 cameraPos = this->camera->getPosition();

	for (Object* obj : this->objects)
	{
		obj->getProgram()->setFloat3("viewPos", cameraPos.x, cameraPos.y, cameraPos.z);
	}

	return this->objects;
}