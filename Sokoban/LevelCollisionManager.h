#pragma once
#include "Level.h"

class LevelCollisionManager
{
public:
	void Manage(Level& level);

private:
	Level* m_level = nullptr;

	TiledEntity* GetEntityCollidingWithCharacter(const Level& level) const;
	bool IsEntityInCollision(const Level& level, const TiledEntity& entity) const;
};
