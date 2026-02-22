

#include "World.h"

#include <algorithm>
#include <iostream>


World::~World()
{
	for (auto ptr : this->objects)
		delete ptr;
}


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
	auto end = 
		std::remove_if(
			this->objects.begin(), 
			this->objects.end(), 
			[id](Object* ptr) {
				if (ptr->id == id && ptr->isRemovable())
				{
					delete ptr;
					return true;
				}
				else
					return false;
			});

	this->objects.erase(end, this->objects.end());
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