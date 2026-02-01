

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


std::vector<Object*>& World::getObjects()
{
	return this->objects;
}