#include "SpriteRenderInfo.h"

SpriteRenderInfo::SpriteRenderInfo(ResourceInterface& bitmapInterface, Vector2i size, int layerIndex) :
    m_bitmapInterface(bitmapInterface), m_size(size), m_targetLayerIndex(layerIndex)
{

}

int SpriteRenderInfo::GetLayerIndex() const
{
    return m_targetLayerIndex;
}

HBITMAP SpriteRenderInfo::GetSprite() const
{
    return reinterpret_cast<HBITMAP>(m_bitmapInterface.Get());
}
