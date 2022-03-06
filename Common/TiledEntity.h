#pragma once
#include "TileRenderInfo.h"

class TiledEntity
{
public:
	static const int tileSize{ 24 };

	TiledEntity(const TileRenderInfo& renderInfo, 
		bool isCollidable, bool isMovable);
	TiledEntity(const TiledEntity&) = delete;

	bool operator==(const TiledEntity& otherEntity);
	bool operator!=(const TiledEntity& otherEntity);
	TiledEntity& operator=(const TiledEntity&) = delete;

	const TileRenderInfo& GetRenderInfo() const;
	Vector2i GetPosition() const; 
	bool IsCollision(const TiledEntity& otherTiledEntity) const;
	virtual void Move(Vector2i translation);

	bool IsCollidable() const;
	bool IsMovable() const;

private:
	Vector2i m_position;
	TileRenderInfo m_renderInfo;

	bool m_isCollidable = false;
	bool m_isMovable = false;
};
