#pragma once
#include "TiledEntity.h"

class TiledEntityFactory
{
public:
	TiledEntityFactory() = delete;
	TiledEntityFactory(const TiledEntityFactory&) = delete;

	TiledEntityFactory& operator=(const TiledEntityFactory&) = delete;

	static std::unique_ptr<TiledEntity> CreateWall();
	static std::unique_ptr<TiledEntity> CreateRoad();
	static std::unique_ptr<TiledEntity> CreateBarrel();
	static std::unique_ptr<TiledEntity> CreateCross();
	static std::unique_ptr<TiledEntity> CreateCharacter();
};
