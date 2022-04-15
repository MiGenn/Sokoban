#include "TiledEntity.h"

#include <stdexcept>
#include "Serializers.h"
#include "TileCollisionDetector.h"
#include "TypeRegistrator.h"

static TypeRegistrator<TiledEntity> registrator;

TiledEntity::TiledEntity(std::ifstream& file)
{
	DeserializeFromOpenedFileToSelf(file);
}

TiledEntity::TiledEntity(const SpriteRenderInfo& renderInfo, Tag tag) :
	m_renderInfo(renderInfo), m_tag(tag)
{

}

TiledEntity::TiledEntity(const SpriteRenderInfo& renderInfo, Tag tag, Vector2i position) :
	TiledEntity(std::move(renderInfo), tag)
{
	m_position = position;
}

TiledEntity::TiledEntity(const TiledEntity& entity)
{
	(*this) = entity;
}

TiledEntity& TiledEntity::operator=(const TiledEntity& right)
{
	m_renderInfo = right.m_renderInfo;
	m_position = right.m_position;
	m_tag = right.m_tag;

	return *this;
}

bool TiledEntity::operator==(const TiledEntity& right) noexcept
{
	return this == &right;
}

bool TiledEntity::operator!=(const TiledEntity& right) noexcept
{
	return !(*this == right);
}

void TiledEntity::SerializeToOpenedFile(std::ofstream& file) const
{
	m_position.SerializeToOpenedFile(file);
	PlainTypeBinarySerializer::SerializeToOpenedFile(m_tag, file);
	m_renderInfo.SerializeToOpenedFile(file);
}

void TiledEntity::DeserializeFromOpenedFileToSelf(std::ifstream& file)
{
	m_position.DeserializeFromOpenedFileToSelf(file);
	PlainTypeBinarySerializer::DeserializeFromOpenedFile(m_tag, file);
	m_renderInfo.DeserializeFromOpenedFileToSelf(file);
}

void TiledEntity::SetPosition(Vector2i newPosition) noexcept
{
	m_position = newPosition;
}

Vector2i TiledEntity::GetPosition() const noexcept
{
	return m_position;
}

TiledEntity::Tag TiledEntity::GetTag() const noexcept
{
	return m_tag;
}

const SpriteRenderInfo& TiledEntity::GetRenderInfo() const noexcept
{
	m_renderInfo.SetPosition(m_position);

	return m_renderInfo;
}

bool TiledEntity::IsCollision(const TiledEntity& otherTiledEntity) const noexcept
{
	return TileCollisionDetector::IsCollision(m_position, otherTiledEntity.m_position);;
}

void TiledEntity::Move(Vector2i translation) noexcept
{
	m_position += translation;	
}
