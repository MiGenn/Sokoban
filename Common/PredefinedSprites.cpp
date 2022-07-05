#include "PredefinedSprites.h"

#include <algorithm>
#include <cassert>

const std::wstring PredefinedSprites::relativeFullPath{ L"Content\\Textures\\GameObjects\\tileSet.bmp" };

const Box2i PredefinedSprites::wallBoundingBox{ { 64 * 0, 0 },
	{ tileSizeInPixels, tileSizeInPixels } };
const Box2i PredefinedSprites::roadBoundingBox{ { 64 * 1, 0 },
	{ tileSizeInPixels, tileSizeInPixels } };
const Box2i PredefinedSprites::boxBoundingBox{ { 64 * 2, 0 },
	{ tileSizeInPixels, tileSizeInPixels } };
const Box2i PredefinedSprites::pointBoundingBox{ { 64 * 3, 0 },
	{ tileSizeInPixels, tileSizeInPixels } };
const Box2i PredefinedSprites::characterBoundingBox{ { 64 * 4, 0 },
	{ tileSizeInPixels, tileSizeInPixels } };

std::vector<std::shared_ptr<Sprite>> PredefinedSprites::m_sprites;
Utilities::Cpp::StaticConstructor PredefinedSprites::m_constructor(Construct);

std::shared_ptr<Sprite> PredefinedSprites::GetSprite(const std::wstring& spriteFullPath) NOEXCEPT_WHEN_NDEBUG
{
	auto spriteIterator{ std::find_if(m_sprites.begin(), m_sprites.end(), 
		[&spriteFullPath](const std::shared_ptr<Sprite>& sprite)
		{
			return sprite->GetFullPath() == spriteFullPath;
		}) };

	assert(spriteIterator != m_sprites.end());
	return *spriteIterator;
}

void PredefinedSprites::Construct() noexcept
{
	m_sprites.push_back(std::make_shared<Sprite>(relativeFullPath));
}
