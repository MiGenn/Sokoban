#include "TileRenderInfo.h"

#include "TiledEntity.h"

TileRenderInfo::TileRenderInfo(const ResourceInterface& bitmapInterface, int layerIndex) :
	SpriteRenderInfo(bitmapInterface, { TiledEntity::tileSize, TiledEntity::tileSize }, layerIndex)
{

}
