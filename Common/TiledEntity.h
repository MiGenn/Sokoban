#pragma once
#include <vector>
#include "Vector2D.h"

class TiledEntity final
{
public:
	static const int tileSize{ 24 };

	TiledEntity() = default;
	TiledEntity(const TiledEntity&) = delete;

	TiledEntity& operator=(const TiledEntity&) = delete;

private:
	Vector2i m_position;

};
