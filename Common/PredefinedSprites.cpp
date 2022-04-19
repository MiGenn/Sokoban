#include "PredefinedSprites.h"

#include <algorithm>
#include <cassert>

const std::wstring PredefinedSprites::wallFullPath{ 
	L"Content\\Textures\\GameObjects\\Wall.bmp" };
const std::wstring PredefinedSprites::roadFullPath{ 
	L"Content\\Textures\\GameObjects\\Road.bmp" };
const std::wstring PredefinedSprites::crossFullPath{ 
	L"Content\\Textures\\GameObjects\\Cross.bmp" };
const std::wstring PredefinedSprites::barrelFullPath{ 
	L"Content\\Textures\\GameObjects\\Barrel.bmp" };
const std::wstring PredefinedSprites::characterFullPath{ 
	L"Content\\Textures\\GameObjects\\Character.bmp" };

std::vector<std::shared_ptr<Sprite>> PredefinedSprites::m_sprites;
StaticConstructor PredefinedSprites::m_constructor(Construct);

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
	m_sprites.push_back(std::make_shared<Sprite>(wallFullPath));
	m_sprites.push_back(std::make_shared<Sprite>(roadFullPath));
	m_sprites.push_back(std::make_shared<Sprite>(crossFullPath));
	m_sprites.push_back(std::make_shared<Sprite>(barrelFullPath));
	m_sprites.push_back(std::make_shared<Sprite>(characterFullPath));
}
