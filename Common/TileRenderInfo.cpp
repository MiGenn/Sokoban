#include "TileRenderInfo.h"

TileRenderInfo::TileRenderInfo(ResourceInterface& bitmapInterface, int size, int layerIndex) :
	SpriteRenderInfo(bitmapInterface, { size, size }, layerIndex)
{

}
