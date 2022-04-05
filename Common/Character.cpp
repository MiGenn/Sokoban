#include "Character.h"

Character::Character(const SpriteRenderInfo& renderInfo) :
	TiledEntity(renderInfo, { 0, 0 }, true, true)
{
	m_previousPosition = GetPosition();
}

Vector2i Character::GetLastTranslation() const
{
	return GetPosition() - m_previousPosition;
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

void Character::Update(const Keyboard& keyboard)
{
	static Vector2i translation;

	if (keyboard.IsKeyPressed('W'))
		translation += Vector2i(0, -1);

	if (keyboard.IsKeyPressed('S'))
		translation += Vector2i(0, 1);

	if (keyboard.IsKeyPressed('A'))
		translation += Vector2i(-1, 0);

	if (keyboard.IsKeyPressed('D'))
		translation += Vector2i(1, 0);

	Move(translation);
}
