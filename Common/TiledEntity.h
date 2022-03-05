#pragma once
#include "TileRenderInfo.h"

class TiledEntity final
{
public:
	static const int tileSize{ 24 };

	TiledEntity(const TileRenderInfo& renderInfo, bool isCollidable);
	TiledEntity(const TiledEntity&) = delete;

	TiledEntity& operator=(const TiledEntity&) = delete;

	const TileRenderInfo& GetRenderInfo() const;
	bool IsCollision(Vector2i otherTilePosition) const;
	bool IsCollidable() const;

private:
	Vector2i m_position;
	TileRenderInfo m_renderInfo;
	bool m_isCollidable;
};
