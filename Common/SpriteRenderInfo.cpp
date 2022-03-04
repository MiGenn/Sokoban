#include "SpriteRenderInfo.h"

SpriteRenderInfo::SpriteRenderInfo(HBITMAP bitmap, int layerIndex)
{
    m_bitmap = bitmap;
    m_targetLayerIndex = layerIndex;
}

int SpriteRenderInfo::GetLayerIndex() const
{
    return m_targetLayerIndex;
}

HBITMAP SpriteRenderInfo::GetSprite() const
{
    return m_bitmap;
}
