#pragma once
#include "Character.h"

namespace TiledEntityFactory
{
	std::unique_ptr<TiledEntity> CreateWall(Vector2i position);
	std::unique_ptr<TiledEntity> CreateRoad(Vector2i position);
	std::unique_ptr<TiledEntity> CreateBarrel(Vector2i position);
	std::unique_ptr<TiledEntity> CreateCross(Vector2i position);
	std::unique_ptr<TiledEntity> CreateCharacter(Vector2i position);
}
