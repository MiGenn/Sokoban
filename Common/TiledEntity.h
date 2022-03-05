#pragma once
#include <vector>
#include "TileRenderInfo.h"

class TiledEntity final
{
public:
	static const int tileSize{ 24 };

	TiledEntity(bool isCollidable = false);
	TiledEntity(const TiledEntity&) = delete;

	TiledEntity& operator=(const TiledEntity&) = delete;

	bool IsCollidable() const;
	const TileRenderInfo& GetRenderInfo();

private:
	Vector2i m_position;
	TileRenderInfo m_renderInfo;
	bool m_isCollidable;
};
