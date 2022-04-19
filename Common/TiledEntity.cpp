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

TiledEntity::TiledEntity(const SpriteRenderInfo& renderInfo, Tag tag, Vector2i positionInUnits) :
	TiledEntity(renderInfo, tag)
{
	m_positionInUnits = positionInUnits;
}

TiledEntity::TiledEntity(const TiledEntity& entity)
{
	(*this) = entity;
}

TiledEntity& TiledEntity::operator=(const TiledEntity& right)
{
	m_renderInfo = right.m_renderInfo;
	m_positionInUnits = right.m_positionInUnits;
	m_tag = right.m_tag;

	return *this;
}

bool TiledEntity::operator==(const TiledEntity& right) noexcept
{
	return m_positionInUnits == right.m_positionInUnits &&
		m_tag == right.m_tag;
}

bool TiledEntity::operator!=(const TiledEntity& right) noexcept
{
	return !(*this == right);
}

void TiledEntity::SerializeToOpenedFile(std::ofstream& file) const
{
	m_positionInUnits.SerializeToOpenedFile(file);
	PlainTypeBinarySerializer::SerializeToOpenedFile(m_tag, file);
	m_renderInfo.SerializeToOpenedFile(file);
}

void TiledEntity::DeserializeFromOpenedFileToSelf(std::ifstream& file)
{
	m_positionInUnits.DeserializeFromOpenedFileToSelf(file);
	PlainTypeBinarySerializer::DeserializeFromOpenedFile(m_tag, file);
	m_renderInfo.DeserializeFromOpenedFileToSelf(file);
}

void TiledEntity::SetPosition(Vector2i newPositionInUnits) noexcept
{
	m_positionInUnits = newPositionInUnits;
}

Vector2i TiledEntity::GetPosition() const noexcept
{
	return m_positionInUnits;
}

TiledEntity::Tag TiledEntity::GetTag() const noexcept
{
	return m_tag;
}

const SpriteRenderInfo& TiledEntity::GetRenderInfo() const noexcept
{
	m_renderInfo.SetPosition(m_positionInUnits);

	return m_renderInfo;
}

bool TiledEntity::IsCollision(const TiledEntity& otherTiledEntity) const noexcept
{
	return TileCollisionDetector::IsCollision(m_positionInUnits, otherTiledEntity.m_positionInUnits);;
}

void TiledEntity::Move(Vector2i translation) noexcept
{
	m_positionInUnits += translation;	
}
