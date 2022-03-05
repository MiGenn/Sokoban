#pragma once
#include "SpriteRenderInfo.h"

class TileRenderInfo final : public SpriteRenderInfo
{
public:
	TileRenderInfo(ResourceInterface& bitmapInterface, int size, int layerIndex);
	TileRenderInfo(const TileRenderInfo&) = delete;

	TileRenderInfo& operator=(const TileRenderInfo&) = delete;
};
