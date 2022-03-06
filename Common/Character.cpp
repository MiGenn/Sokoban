#include "Character.h"

Character::Character(const TileRenderInfo& renderInfo) :
	TiledEntity(renderInfo, true, true)
{
	m_previousPosition = GetPosition();
}

Vector2i Character::GetPreviousPosition() const
{
	return m_previousPosition;
}

void Character::Move(Vector2i translation)
{
	m_previousPosition = GetPosition();
	TiledEntity::Move(translation);
}

void Character::RevertToPreviousPosition()
{
	SetPosition(m_previousPosition);
}
