#pragma once
#include "TiledEntity.h"

namespace TiledEntityFactory
{
	std::unique_ptr<TiledEntity> CreateWall();
	std::unique_ptr<TiledEntity> CreateRoad();
	std::unique_ptr<TiledEntity> CreateBarrel();
	std::unique_ptr<TiledEntity> CreateCross();
	std::unique_ptr<TiledEntity> CreateCharacter();
}
