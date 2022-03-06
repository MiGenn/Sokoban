#pragma once
#include "Character.h"

class TiledEntityFactory
{
public:
	static TiledEntity* CreateWall(Vector2i position);
	static TiledEntity* CreateRoad(Vector2i position);
	static TiledEntity* CreateBarrel(Vector2i position);
	static TiledEntity* CreateCross(Vector2i position);
};
