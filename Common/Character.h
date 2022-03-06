#pragma once
#include "TiledEntity.h"

class Character : public TiledEntity
{
public:
	Character(const TileRenderInfo& renderInfo);
	Character(const Character&) = delete;

	Character& operator=(const Character&) = delete;

	Vector2i GetPreviousPosition() const;
	void Move(Vector2i translation) override;
	void RevertToPreviousPosition();

private:
	Vector2i m_previousPosition;
};
