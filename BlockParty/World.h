#pragma once

#include <vector>

#include "Object.h"
#include "ModelContainer.h"


class World : public ModelContainer
{
private:
	std::vector<Object*> objects{};

public:
	void addObject(Object* object);

	void removeObject(unsigned int id);

	void processModels(void (*modelFunc)(Model*)) override;
};