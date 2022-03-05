#pragma once
#include "SpriteRenderInfo.h"

class TileRenderInfo final : public SpriteRenderInfo
{
public:
	TileRenderInfo(const ResourceInterface& bitmapInterface, int layerIndex);
};
