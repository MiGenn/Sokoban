#include "TiledEntityFactory.h"

#include "PredefinedSprites.h"

static const Box2i tileBoundingBox{ { 0, 0 }, { TiledEntity::tileSize, TiledEntity::tileSize } };

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateWall()
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::wallFullPath), 
		{}, tileBoundingBox, 0 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Wall);
}

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateRoad()
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::roadFullPath),
		{}, tileBoundingBox, 0 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Road);
}

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateBarrel()
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::barrelFullPath),
		{}, tileBoundingBox, 1 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Barrel);
}

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateCross()
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::crossFullPath),
		{}, tileBoundingBox, 0 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Cross);
}

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateCharacter()
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::characterFullPath),
		{}, tileBoundingBox, 1 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Character);
}
