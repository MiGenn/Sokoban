#include "TiledEntityFactory.h"

#include "PredefinedSprites.h"

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateWall()
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::relativeFullPath),
		PredefinedSprites::wallBoundingBox, 0, };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Wall);
}

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateRoad()
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::relativeFullPath),
		PredefinedSprites::roadBoundingBox, 0 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Road);
}

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateBox()
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::relativeFullPath),
		PredefinedSprites::boxBoundingBox, 1 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Box);
}

std::unique_ptr<TiledEntity> TiledEntityFactory::CreatePoint()
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::relativeFullPath),
		PredefinedSprites::pointBoundingBox, 0 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Point);
}

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateCharacter()
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::relativeFullPath),
		PredefinedSprites::characterBoundingBox, 1 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Character);
}
