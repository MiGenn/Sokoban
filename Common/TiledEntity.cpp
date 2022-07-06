#include "TiledEntity.h"

#include <stdexcept>
#include "NumberComparison.h"
#include "Serializers.h"
#include "TypeRegistrator.h"
#include "Collision2D.h"

static TypeRegistrator<TiledEntity> registrator;

TiledEntity::TiledEntity(std::ifstream& file)
{
	DeserializeFromOpenedFileToSelf(file);
}

TiledEntity::TiledEntity(const SpriteRenderInfo& renderInfo, Tag tag) noexcept :
	m_renderInfo(renderInfo), m_tag(tag)
{

}

TiledEntity::TiledEntity(const SpriteRenderInfo& renderInfo, Tag tag, Vector2f position) noexcept :
	TiledEntity(renderInfo, tag)
{
	m_position = position;
}

TiledEntity::TiledEntity(const TiledEntity& entity) noexcept
{
	(*this) = entity;
}

TiledEntity& TiledEntity::operator=(const TiledEntity& right) noexcept
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

bool TiledEntity::IsCollision(const TiledEntity& otherEntity) const noexcept
{
	return Collision2D::IsCollision(m_position, m_renderInfo.GetSize(),
		otherEntity.GetPosition(), otherEntity.GetRenderInfo().GetSize());
}

bool TiledEntity::IsInTheSamePosition(const TiledEntity& otherEntity) const noexcept
{
	static const auto epsilon{ Utilities::Cpp::epsilonF };
	auto otherEntityPosition{ otherEntity.GetPosition() };

	return Utilities::Cpp::AreEqual(m_position.x, otherEntityPosition.x, epsilon) &&
		Utilities::Cpp::AreEqual(m_position.y, otherEntityPosition.y, epsilon);
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

void TiledEntity::SetPosition(Vector2f newPosition) noexcept
{
	m_position = newPosition;
}

Vector2f TiledEntity::GetPosition() const noexcept
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

void TiledEntity::SerializeIDToOpenedFile(std::ofstream& file) const
{
	IBinarySerializable::SerializeIDToOpenedFile<TiledEntity>(file);
}

void TiledEntity::Move(Vector2f translation) noexcept
{
	m_position += translation;	
}
