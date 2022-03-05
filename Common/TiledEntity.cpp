#include "TiledEntity.h"

#include "TileCollisionDetector.h"

TiledEntity::TiledEntity(const TileRenderInfo& renderInfo, bool isCollidable) :
	m_isCollidable(isCollidable), m_renderInfo(renderInfo)
{

}

bool TiledEntity::IsCollidable() const
{
	return m_isCollidable;
}

const TileRenderInfo& TiledEntity::GetRenderInfo() const
{
	return m_renderInfo;
}

bool TiledEntity::IsCollision(Vector2i otherTilePosition) const
{
	return TileCollisionDetector::IsCollision(m_position, otherTilePosition);
}
