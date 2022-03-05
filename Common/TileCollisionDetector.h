#pragma once
#include "Vector2D.h"

class TileCollisionDetector
{
public:
	static bool IsCollision(Vector2i tilePosition1, Vector2i tilePosition2);
};
