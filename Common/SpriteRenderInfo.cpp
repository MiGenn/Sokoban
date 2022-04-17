#include "SpriteRenderInfo.h"

#include <cassert>
#include "Serializers.h"

SpriteRenderInfo::SpriteRenderInfo(std::shared_ptr<Sprite> sprite, 
    Vector2i position, Box2i boundingBox, int layerIndex) NOEXCEPT_WHEN_NDEBUG :   
    m_sprite(std::move(sprite)), m_screenPosition(position), 
    m_boundingBox(boundingBox), m_layerIndex(layerIndex)
{
    assert(m_sprite->IsEmpty() != true);
    assert(boundingBox.GetPosition().x >= 0 && 
        boundingBox.GetPosition().y >= 0);
}

SpriteRenderInfo::SpriteRenderInfo() noexcept :
    m_sprite(std::make_shared<Sprite>())
{

}

SpriteRenderInfo::SpriteRenderInfo(const SpriteRenderInfo& spriteRenderInfo) noexcept
{
    (*this) = spriteRenderInfo;
}

SpriteRenderInfo& SpriteRenderInfo::operator=(const SpriteRenderInfo& right) noexcept
{
    m_sprite = right.m_sprite;
    m_boundingBox = right.m_boundingBox;
    m_screenPosition = right.m_screenPosition;
    m_layerIndex = right.m_layerIndex;

    return *this;
}

void SpriteRenderInfo::SetPosition(Vector2i newPosition) noexcept
{
    m_screenPosition = newPosition;
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
    return m_sprite->IsEmpty();
}

HBITMAP SpriteRenderInfo::GetBitmap() const noexcept
{
    return m_sprite->GetBitmap();
}

Box2i SpriteRenderInfo::GetBoundingBox() const noexcept
{
    return m_boundingBox;
}

Vector2i SpriteRenderInfo::GetScreenPosition() const noexcept
{
    return m_screenPosition;
}

int SpriteRenderInfo::GetLayerIndex() const noexcept
{
    return m_layerIndex;
}

void SpriteRenderInfo::SerializeToOpenedFile(std::ofstream& file) const
{
    m_sprite->SerializeToOpenedFile(file);
    m_boundingBox.SerializeToOpenedFile(file);
    m_screenPosition.SerializeToOpenedFile(file);
    PlainTypeBinarySerializer::SerializeToOpenedFile(m_layerIndex, file);
}

void SpriteRenderInfo::DeserializeFromOpenedFileToSelf(std::ifstream& file)
{
    m_sprite->DeserializeFromOpenedFileToSelf(file);
    m_boundingBox.DeserializeFromOpenedFileToSelf(file);
    m_screenPosition.DeserializeFromOpenedFileToSelf(file);
    PlainTypeBinarySerializer::DeserializeFromOpenedFile(m_layerIndex, file);
}
