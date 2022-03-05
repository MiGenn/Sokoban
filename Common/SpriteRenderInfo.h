#pragma once
#include "BitmapLoader.h"
#include "ResourceInterface.h"
#include "Vector2D.h"

class SpriteRenderInfo
{
public:
	SpriteRenderInfo(ResourceInterface& bitmapInterface, Vector2i size, int layerIndex);
	SpriteRenderInfo(const SpriteRenderInfo&) = delete;

	SpriteRenderInfo& operator=(const SpriteRenderInfo&) = delete;

	int GetLayerIndex() const;
	HBITMAP GetSprite() const;

private:  
	ResourceInterface m_bitmapInterface;
	Vector2i m_size;
	int m_targetLayerIndex = 0;
};
