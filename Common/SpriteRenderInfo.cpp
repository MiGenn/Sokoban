#include "SpriteRenderInfo.h"

SpriteRenderInfo::SpriteRenderInfo(HBITMAP sprite, int layerIndex)
{
    m_sprite = sprite;
    m_targetLayerIndex = layerIndex;
}

void SpriteRenderInfo::Update()
{

}

int SpriteRenderInfo::GetLayerNumber() const
{
    return m_targetLayerIndex;
}

HBITMAP SpriteRenderInfo::GetSprite() const
{
    return m_sprite;
}
