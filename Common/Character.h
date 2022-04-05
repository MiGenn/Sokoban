#pragma once
#include "TiledEntity.h"
#include "Keyboard.h"

class Character : public TiledEntity
{
public:
	Character(const SpriteRenderInfo& renderInfo);

	Vector2i GetLastTranslation() const;
	Vector2i GetPreviousPosition() const;
	void Move(Vector2i translation) override;
	void RevertToPreviousPosition();

	void Update(const Keyboard& keyboard);

private:
	Vector2i m_previousPosition;
};
