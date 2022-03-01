#pragma once
#include "Entity2D.h"

class Scene
{
public:
	std::vector<Entity2D*> entities;

	Scene() = default;
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;
};
