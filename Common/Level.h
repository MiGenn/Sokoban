#pragma once
#include <string>
#include "TiledEntity.h"

class Level final
{
public:
	static const std::string relativePath;
	static const std::string extension;

	Vector2i characterStartPosition;
	std::vector<TiledEntity> entities;

	Level() = default;
	Level(const Level&) = delete;

	Level& operator=(const Level&) = delete;
};
