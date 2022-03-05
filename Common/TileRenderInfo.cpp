#include "TileRenderInfo.h"

#include "TiledEntity.h"

TileRenderInfo::TileRenderInfo(const ResourceInterface& bitmapInterface, 
	Vector2i position, Box2i boundingBox, int layerIndex) :
	SpriteRenderInfo(bitmapInterface, position, boundingBox, layerIndex)
{

}
