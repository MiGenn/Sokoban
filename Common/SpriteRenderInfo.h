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

	void SetPosition(Vector2i newPosition) noexcept;

	ResourceInterface GetBitmapInterface() const noexcept;
	HBITMAP GetBitmap() const noexcept;
	int GetLayerIndex() const noexcept;
	Box2i GetBoundingBox() const noexcept;
	Vector2i GetPosition() const noexcept;

private:  
	ResourceInterface m_bitmapInterface;
	int m_targetLayerIndex = 0;
	Vector2i m_position;
	Box2i m_boundingBox;
};
