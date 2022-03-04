#include "TileCollider.h"

TileCollider::TileCollider(const TiledEntity* owner) :
	m_owner(owner)
{

}

bool TileCollider::IsCollision(const TileCollider& tileCollider)
{
	return false;
}
