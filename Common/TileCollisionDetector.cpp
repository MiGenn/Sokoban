#include "TileCollisionDetector.h"

#include "TiledEntity.h"

bool TileCollisionDetector::IsCollision(Vector2i tilePosition1, Vector2i tilePosition2)
{
    return tilePosition1 == tilePosition2;
}
