

#include "World.h"

#include <algorithm>


void World::addObject(Object* object)
{
	this->objects.push_back(object);
}


void World::removeObject(unsigned int id)
{
	std::remove_if(
		this->objects.begin(), 
		this->objects.end(), 
		[id](auto ptr) { return ptr->id == id; });
}


void World::processModels(void (*modelFunc)(Model*))
{
	std::for_each(
		this->objects.begin(),
		this->objects.end(),
		[modelFunc](Object* object) {
			modelFunc(object->getModel());
		});
}