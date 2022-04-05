#include "SpriteRenderInfo.h"

#include <cassert>

SpriteRenderInfo::SpriteRenderInfo(const ResourceInterface& bitmapInterface, 
    Vector2i position, Box2i boundingBox, int layerIndex) :
    m_bitmapInterface(bitmapInterface), m_position(position), 
    m_boundingBox(boundingBox), m_targetLayerIndex(layerIndex)
{
    assert(boundingBox.GetPosition().x > 0 && boundingBox.GetPosition().y > 0);
}

void SpriteRenderInfo::SetPosition(Vector2i newPosition) noexcept
{
    m_position = newPosition;
}

ResourceInterface SpriteRenderInfo::GetBitmapInterface() const noexcept
{
    return m_bitmapInterface;
}

HBITMAP SpriteRenderInfo::GetBitmap() const noexcept
{
    return reinterpret_cast<HBITMAP>(m_bitmapInterface.Get());
}

int SpriteRenderInfo::GetLayerIndex() const noexcept
{
    return m_targetLayerIndex;
}

Box2i SpriteRenderInfo::GetBoundingBox() const noexcept
{
    return m_boundingBox;
}

Vector2i SpriteRenderInfo::GetPosition() const noexcept
{
    return m_position;
}
