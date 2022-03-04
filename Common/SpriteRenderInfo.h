#pragma once
#include "BitmapLoader.h"

class SpriteRenderInfo
{
public:
	SpriteRenderInfo(HBITMAP bitmap, int layerIndex);
	SpriteRenderInfo(const SpriteRenderInfo&) = delete;

	SpriteRenderInfo& operator=(const SpriteRenderInfo&) = delete;

	int GetLayerIndex() const;
	HBITMAP GetSprite() const;

private:
	HBITMAP m_bitmap;
	int m_targetLayerIndex = 0;
};
