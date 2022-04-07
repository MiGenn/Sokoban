#include "TiledEntityFactory.h"

static const Box2i tileBoundingBox{ { 0, 0 }, { TiledEntity::tileSize, TiledEntity::tileSize } };

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateWall(Vector2i position)
{
	SpriteRenderInfo renderInfo{ Sprites::GetSprite(Sprites::wallFullRelativePath), 
		position, tileBoundingBox, 0};

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Wall, position);
}

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateRoad(Vector2i position)
{
	SpriteRenderInfo renderInfo{ Sprites::GetSprite(Sprites::roadFullRelativePath),
		position, tileBoundingBox, 0 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Road, position);
}

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateBarrel(Vector2i position)
{
	SpriteRenderInfo renderInfo{ Sprites::GetSprite(Sprites::barrelFullRelativePath),
		position, tileBoundingBox, 0 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Barrel, position);
}

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateCross(Vector2i position)
{
	SpriteRenderInfo renderInfo{ Sprites::GetSprite(Sprites::crossFullRelativePath),
		position, tileBoundingBox, 0 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Cross, position);
}

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateCharacter(Vector2i position)
{
	SpriteRenderInfo renderInfo{ Sprites::GetSprite(Sprites::characterFullRelativePath),
		position, tileBoundingBox, 0 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Character, position);
}
