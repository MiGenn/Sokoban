#pragma once
#include "TiledEntity.h"

class TiledEntityFactory
{
public:
	TiledEntityFactory() = delete;
	TiledEntityFactory(const TiledEntityFactory&) = delete;

	TiledEntityFactory& operator=(const TiledEntityFactory&) = delete;

	static std::unique_ptr<TiledEntity> CreateWall() NOEXCEPT_WHEN_NDEBUG;
	static std::unique_ptr<TiledEntity> CreateRoad() NOEXCEPT_WHEN_NDEBUG;
	static std::unique_ptr<TiledEntity> CreateBox() NOEXCEPT_WHEN_NDEBUG;
	static std::unique_ptr<TiledEntity> CreatePoint() NOEXCEPT_WHEN_NDEBUG;
	static std::unique_ptr<TiledEntity> CreateCharacter() NOEXCEPT_WHEN_NDEBUG;
};
