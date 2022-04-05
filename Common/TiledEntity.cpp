#include "TiledEntity.h"

#include <stdexcept>
#include "TileCollisionDetector.h"

//TiledEntity::TiledEntity(std::ifstream& file)
//{
//	BinaryDeserializeFromOpenedFileToSelf(file);
//{

TiledEntity::TiledEntity(const SpriteRenderInfo& renderInfo,
	Vector2i position, bool isCollidable, bool isMovable) :
	m_renderInfo(renderInfo), m_position(position), 
	m_isCollidable(isCollidable), m_isMovable(isMovable)
{ 
	if (isMovable && !isCollidable)
		throw std::runtime_error("Incorrect parameters!");
}

bool TiledEntity::operator==(const TiledEntity& otherEntity)
{
	return this == &otherEntity;
}

bool TiledEntity::operator!=(const TiledEntity& otherEntity)
{
	return !(*this == otherEntity);
}

bool TiledEntity::IsCollidable() const
{
	return m_isCollidable;
}

bool TiledEntity::IsMovable() const
{
	return m_isMovable;
}

void TiledEntity::BinarySerializeToOpenedFile(std::ofstream& file) const
{
}

void TiledEntity::BinaryDeserializeFromOpenedFileToSelf(std::ifstream& file)
{
}

void TiledEntity::SetPosition(Vector2i newPosition)
{
	m_position = newPosition;
}

const SpriteRenderInfo& TiledEntity::GetRenderInfo() const
{
	m_renderInfo.SetPosition(m_position);

	return m_renderInfo;
}

Vector2i TiledEntity::GetPosition() const
{
	return m_position;
}

bool TiledEntity::IsCollision(const TiledEntity& otherTiledEntity) const
{
	if (m_isCollidable && otherTiledEntity.m_isCollidable)
		return TileCollisionDetector::IsCollision(m_position, otherTiledEntity.m_position);
	
	return false;
}

void TiledEntity::Move(Vector2i translation)
{
	if (m_isMovable)
		m_position += translation;
}
