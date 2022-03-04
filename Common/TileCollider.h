#pragma once
#include "TiledEntity.h"

class TileCollider
{
public:
	TileCollider(const TiledEntity* owner);
	TileCollider(const TileCollider&) = delete;

	TileCollider& operator=(const TileCollider&) = delete;

	bool IsCollision(const TileCollider& tileCollider);

private:
	const TiledEntity* const m_owner;
};
