#pragma once
#include "Window.h"
#include "Component.h"

class SpriteRenderInfo : public Component
{
public:
	SpriteRenderInfo(HBITMAP sprite, int layerIndex);
	SpriteRenderInfo(const SpriteRenderInfo&) = delete;
	SpriteRenderInfo& operator=(const SpriteRenderInfo&) = delete;

	void Update() override final;
	int GetLayerNumber() const;
	HBITMAP GetSprite() const;

private:
	HBITMAP m_sprite;
	int m_targetLayerIndex = 0;
};
