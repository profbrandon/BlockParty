#pragma once

#include <vector>

#include "Object.h"


class ObjectContainer
{
public:
	virtual std::vector<Object*>& getObjects() = 0;
};