#include "SpriteRenderInfo.h"

#include <cassert>
#include "Serializers.h"

SpriteRenderInfo::SpriteRenderInfo(Sprite&& sprite, Vector2i position, 
    Box2i boundingBox, int layerIndex) NOEXCEPT_WHEN_NDEBUG
{
    assert(sprite.IsEmptyBitmap() != false);
    assert(boundingBox.GetPosition().x > 0 && 
        boundingBox.GetPosition().y > 0);

    m_sprite = std::move(sprite);
}

SpriteRenderInfo::SpriteRenderInfo(SpriteRenderInfo&& spriteRenderInfo) noexcept
{
    (*this) = std::move(spriteRenderInfo);
}

SpriteRenderInfo& SpriteRenderInfo::operator=(SpriteRenderInfo&& right) noexcept
{
    m_sprite = std::move(right.m_sprite);
    m_boundingBox = right.m_boundingBox;
    m_worldPosition = right.m_worldPosition;
    m_layerIndex = right.m_layerIndex;

    return *this;
}

void SpriteRenderInfo::SetPosition(Vector2i newPosition) noexcept
{
    m_worldPosition = newPosition;
}

void SpriteRenderInfo::SetBoundingBox(Box2i newBoundingBox) noexcept
{
    m_boundingBox = newBoundingBox;
}

void SpriteRenderInfo::SetLayerIndex(int newLayerIndex) noexcept
{
    m_layerIndex = newLayerIndex;
}

bool SpriteRenderInfo::IsEmptySprite() const noexcept
{
    return m_sprite.IsEmptyBitmap();
}

HBITMAP SpriteRenderInfo::GetSpriteBitmap() const noexcept
{
    return m_sprite.GetBitmap();
}

Box2i SpriteRenderInfo::GetBoundingBox() const noexcept
{
    return m_boundingBox;
}

Vector2i SpriteRenderInfo::GetWorldPosition() const noexcept
{
    return m_worldPosition;
}

int SpriteRenderInfo::GetLayerIndex() const noexcept
{
    return m_layerIndex;
}

void SpriteRenderInfo::SerializeToOpenedFile(std::ofstream& file) const
{
    m_sprite.SerializeToOpenedFile(file);
    m_boundingBox.SerializeToOpenedFile(file);
    m_worldPosition.SerializeToOpenedFile(file);
    PlainTypeBinarySerializer::SerializeToOpenedFile(m_layerIndex, file);
}

void SpriteRenderInfo::DeserializeFromOpenedFileToSelf(std::ifstream& file)
{
    m_sprite.DeserializeFromOpenedFileToSelf(file);
    m_boundingBox.DeserializeFromOpenedFileToSelf(file);
    m_worldPosition.DeserializeFromOpenedFileToSelf(file);
    PlainTypeBinarySerializer::DeserializeFromOpenedFile(m_layerIndex, file);
}
