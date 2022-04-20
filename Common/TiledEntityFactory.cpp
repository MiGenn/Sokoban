#include "TiledEntityFactory.h"

#include "PredefinedSprites.h"

static const Box2i tileBoundingBox{ { 0, 0 }, { TiledEntity::tileSize, TiledEntity::tileSize } };
static constexpr float sizeInUnits{ 1.f };

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateWall()
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::wallFullPath), 
		tileBoundingBox, sizeInUnits, 0 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Wall);
}

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateRoad()
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::roadFullPath), 
		tileBoundingBox, sizeInUnits, 0 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Road);
}

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateBarrel()
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::barrelFullPath), 
		tileBoundingBox, sizeInUnits, 1 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Barrel);
}

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateCross()
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::crossFullPath), 
		tileBoundingBox, sizeInUnits, 0 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Cross);
}

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateCharacter()
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::characterFullPath), 
		tileBoundingBox, sizeInUnits, 1 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Character);
}
