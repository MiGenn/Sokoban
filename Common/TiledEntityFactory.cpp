#include "TiledEntityFactory.h"

#include "PredefinedSprites.h"

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateWall() NOEXCEPT_WHEN_NDEBUG
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::tileSetRelativeFullPath),
		PredefinedSprites::wallBoundingBox, 0, };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Wall);
}

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateRoad() NOEXCEPT_WHEN_NDEBUG
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::tileSetRelativeFullPath),
		PredefinedSprites::roadBoundingBox, 0 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Road);
}

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateBox() NOEXCEPT_WHEN_NDEBUG
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::tileSetRelativeFullPath),
		PredefinedSprites::boxBoundingBox, 1 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Box);
}

std::unique_ptr<TiledEntity> TiledEntityFactory::CreatePoint() NOEXCEPT_WHEN_NDEBUG
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::tileSetRelativeFullPath),
		PredefinedSprites::pointBoundingBox, 0 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Point);
}

std::unique_ptr<TiledEntity> TiledEntityFactory::CreateCharacter() NOEXCEPT_WHEN_NDEBUG
{
	SpriteRenderInfo renderInfo{ PredefinedSprites::GetSprite(PredefinedSprites::tileSetRelativeFullPath),
		PredefinedSprites::characterBoundingBox, 1 };

	return std::make_unique<TiledEntity>(std::move(renderInfo), TiledEntity::Tag::Character);
}
