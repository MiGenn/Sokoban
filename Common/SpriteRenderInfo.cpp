#include "SpriteRenderInfo.h"

SpriteRenderInfo::SpriteRenderInfo(const ResourceInterface& bitmapInterface, 
    Vector2i position, Box2i boundingBox, int layerIndex) :
    m_bitmapInterface(bitmapInterface), m_position(position), 
    m_boundingBox(boundingBox), m_targetLayerIndex(layerIndex)
{

}

HBITMAP SpriteRenderInfo::GetBitmap() const
{
    return reinterpret_cast<HBITMAP>(m_bitmapInterface.Get());
}

int SpriteRenderInfo::GetLayerIndex() const
{
    return m_targetLayerIndex;
}

Box2i SpriteRenderInfo::GetBoundingBox() const
{
    return m_boundingBox;
}

Vector2i SpriteRenderInfo::GetPosition() const
{
    return m_position;
}
