#include "SpriteRenderInfo.h"

#include <cassert>
#include "Serializers.h"

SpriteRenderInfo::SpriteRenderInfo(std::shared_ptr<Sprite> sprite, const Box2i& boundingBox, int layerIndex,
    bool isPreservingAspectRatio, Vector2f size) NOEXCEPT_WHEN_NDEBUG :
    m_sprite(std::move(sprite)), m_boundingBox(boundingBox), m_layerIndex(layerIndex),
    m_isPreservingAspectRatio(isPreservingAspectRatio), m_size(size)
{
    assert(m_size.x >= 0 && m_size.y >= 0);
    assert(m_sprite->IsEmpty() != true);
    assert(boundingBox.GetPosition().x >= 0 && 
        boundingBox.GetPosition().y >= 0);
}

SpriteRenderInfo::SpriteRenderInfo(const SpriteRenderInfo& spriteRenderInfo) noexcept
{
    (*this) = spriteRenderInfo;
}

SpriteRenderInfo& SpriteRenderInfo::operator=(const SpriteRenderInfo& right) noexcept
{
    m_sprite = right.m_sprite;
    m_boundingBox = right.m_boundingBox;
    m_position = right.m_position;
    m_size = right.m_size;
    m_layerIndex = right.m_layerIndex;
    m_isPreservingAspectRatio = right.m_isPreservingAspectRatio;

    return *this;
}

void SpriteRenderInfo::SetPosition(Vector2f newPosition) noexcept
{
    m_position = newPosition;
}

void SpriteRenderInfo::SetBoundingBox(const Box2i& newBoundingBox) noexcept
{
    m_boundingBox = newBoundingBox;
}

void SpriteRenderInfo::SetSize(Vector2f newSize)
{
    if (newSize.x < 0.f || newSize.y || 0.f)
        std::logic_error("The size is incorrect");

    m_size = newSize;
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

Vector2f SpriteRenderInfo::GetPosition() const noexcept
{
    return m_position;
}

Vector2f SpriteRenderInfo::GetSize() const noexcept
{
    return m_size;
}

bool SpriteRenderInfo::IsPreservingAspectRatio() const noexcept
{
    return m_isPreservingAspectRatio;
}

int SpriteRenderInfo::GetLayerIndex() const noexcept
{
    return m_layerIndex;
}

void SpriteRenderInfo::SerializeIDToOpenedFile(std::ofstream& file) const
{
    IBinarySerializable::SerializeIDToOpenedFile<SpriteRenderInfo>(file);
}

void SpriteRenderInfo::SerializeToOpenedFile(std::ofstream& file) const
{
    m_sprite->SerializeToOpenedFile(file);
    m_boundingBox.SerializeToOpenedFile(file);
    m_position.SerializeToOpenedFile(file);
    m_size.SerializeToOpenedFile(file);
    PlainTypeBinarySerializer::SerializeToOpenedFile(m_layerIndex, file);
    PlainTypeBinarySerializer::SerializeToOpenedFile(m_isPreservingAspectRatio, file);
}

void SpriteRenderInfo::DeserializeFromOpenedFileToSelf(std::ifstream& file)
{
    m_sprite->DeserializeFromOpenedFileToSelf(file);
    m_boundingBox.DeserializeFromOpenedFileToSelf(file);
    m_position.DeserializeFromOpenedFileToSelf(file);
    m_size.DeserializeFromOpenedFileToSelf(file);
    PlainTypeBinarySerializer::DeserializeFromOpenedFile(m_layerIndex, file);
    PlainTypeBinarySerializer::DeserializeFromOpenedFile(m_isPreservingAspectRatio, file);
}
