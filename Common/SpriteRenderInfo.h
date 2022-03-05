#pragma once
#include "WinapiException.h"
#include "BitmapLoader.h"
#include "ResourceInterface.h"
#include "Box2D.h"

class SpriteRenderInfo
{
public:
	SpriteRenderInfo(const ResourceInterface& bitmapInterface, 
		Vector2i position, Box2i boundingBox, int layerIndex);

	HBITMAP GetBitmap() const;
	int GetLayerIndex() const;
	Box2i GetBoundingBox() const;
	Vector2i GetPosition() const;

private:  
	ResourceInterface m_bitmapInterface;
	int m_targetLayerIndex = 0;
	Vector2i m_position;
	Box2i m_boundingBox;
};
