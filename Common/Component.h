#pragma once
#include "Object.h"

class Component : public Object
{
public:
	Component() = default;
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;

	virtual void Update() = 0;
};
