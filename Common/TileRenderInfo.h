#pragma once
#include "SpriteRenderInfo.h"

class TileRenderInfo final : public SpriteRenderInfo
{
public:
	TileRenderInfo(const ResourceInterface& bitmapInterface, Vector2i position, Box2i boundingBox, int layerIndex);
};
