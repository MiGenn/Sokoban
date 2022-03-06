#pragma once
#include "Character.h"

class TiledEntityFactory
{
public:
	static TiledEntity* CreateWall();
	static TiledEntity* CreateRoad();
	static TiledEntity* CreateBarrel();
	static TiledEntity* CreateCross();
};
