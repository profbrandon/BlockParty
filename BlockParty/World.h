#pragma once

#include <vector>

#include "Camera.h"
#include "Object.h"
#include "ObjectContainer.h"


class World : public ObjectContainer
{
private:
	Camera* camera = nullptr;

	std::vector<Object*> objects{};

public:
	void addObject(Object* object);

	void setCamera(Camera* camera);

	void removeObject(unsigned int id);

	std::vector<Object*>& getObjects() override;
};