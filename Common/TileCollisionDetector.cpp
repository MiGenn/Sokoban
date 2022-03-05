#include "TileCollisionDetector.h"

#include "TiledEntity.h"

bool TileCollisionDetector::IsCollision(Vector2i tilePosition1, Vector2i tilePosition2)
{
    static bool firstTest = false;
    if (tilePosition2.x < tilePosition1.x + TiledEntity::tileSize &&
        tilePosition2.y < tilePosition1.y + TiledEntity::tileSize)
        firstTest = true;

    static bool secondTest = false;
    if (tilePosition1.x < tilePosition2.x + TiledEntity::tileSize &&
        tilePosition1.y < tilePosition2.y + TiledEntity::tileSize)
        secondTest = true;

    return firstTest && secondTest;
}
