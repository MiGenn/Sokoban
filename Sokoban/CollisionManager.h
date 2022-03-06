#pragma once
#include "Level.h"

class CollisionManager
{
public:
	void Manage(Level& level);

private:
	TiledEntity* GetEntityCollidingWithCharacter(const Level& level) const;
	bool IsEntityInCollision(const Level& level, const TiledEntity& entity) const;
};
