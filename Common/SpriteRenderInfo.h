#pragma once
#include "WinapiException.h"
#include "BitmapLoader.h"
#include "ResourceInterface.h"
#include "Vector2D.h"

class SpriteRenderInfo
{
public:
	SpriteRenderInfo(const ResourceInterface& bitmapInterface, Vector2i size, int layerIndex);

	int GetLayerIndex() const;
	HBITMAP GetSprite() const;

private:  
	ResourceInterface m_bitmapInterface;
	Vector2i m_size;
	int m_targetLayerIndex = 0;
};
