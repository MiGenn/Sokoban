#include "TiledEntity.h"

TiledEntity::TiledEntity(bool isCollidable) :
	m_isCollidable(isCollidable)
{

}

bool TiledEntity::IsCollidable() const
{
	return m_isCollidable;
}

const TileRenderInfo& TiledEntity::GetRenderInfo()
{
	return m_renderInfo;
}
