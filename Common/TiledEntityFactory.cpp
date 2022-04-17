#include "TiledEntityFactory.h"

#include "PredefinedSprites.h"

static const Box2i tileBoundingBox{ { 0, 0 }, { TiledEntity::tileSize, TiledEntity::tileSize } };

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateWall()
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::wallFullRelativePath), 
		{}, tileBoundingBox, 0 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Wall);
}

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateRoad()
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::roadFullRelativePath),
		{}, tileBoundingBox, 0 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Road);
}

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateBarrel()
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::barrelFullRelativePath),
		{}, tileBoundingBox, 1 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Barrel);
}

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateCross()
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::crossFullRelativePath),
		{}, tileBoundingBox, 0 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Cross);
}

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateCharacter()
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::characterFullRelativePath),
		{}, tileBoundingBox, 1 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Character);
}
