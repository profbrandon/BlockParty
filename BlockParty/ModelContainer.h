#pragma once

#include <vector>

#include "Model.h"


class ModelContainer
{
public:
	virtual void processModels(void (*modelFunc)(Model*)) = 0;
};