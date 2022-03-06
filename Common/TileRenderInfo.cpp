#include "TileRenderInfo.h"

#include "TiledEntity.h"

TileRenderInfo::TileRenderInfo(const ResourceInterface& bitmapInterface, 
	Box2i boundingBox, int layerIndex) :
	SpriteRenderInfo(bitmapInterface, Vector2i(), boundingBox, layerIndex)
{

}
