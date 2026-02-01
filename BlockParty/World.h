#pragma once

#include <vector>

#include "Object.h"
#include "ObjectContainer.h"


class World : public ObjectContainer
{
private:
	std::vector<Object*> objects{};

public:
	void addObject(Object* object);

	void removeObject(unsigned int id);

	std::vector<Object*>& getObjects() override;
};