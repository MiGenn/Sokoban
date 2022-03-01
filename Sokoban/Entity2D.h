#pragma once
#include <vector>
#include "Vector2D.h"
#include "Transform2D.h"

class Entity2D : public Object
{
public:
	static constexpr int transformIndex = 0;
	static constexpr int renderInfoIndex = 1;
	std::vector<Component*> components;  

	Entity2D();
	Entity2D(const Entity2D&) = delete;
	Entity2D& operator=(const Entity2D&) = delete;
};
