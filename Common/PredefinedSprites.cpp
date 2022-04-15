#include "PredefinedSprites.h"

#include <algorithm>
#include <cassert>

const std::wstring PredefinedSprites::wallFullRelativePath{ 
	L"Content\\Textures\\GameObjects\\Wall.bmp" };
const std::wstring PredefinedSprites::roadFullRelativePath{ 
	L"Content\\Textures\\GameObjects\\Road.bmp" };
const std::wstring PredefinedSprites::crossFullRelativePath{ 
	L"Content\\Textures\\GameObjects\\Cross.bmp" };
const std::wstring PredefinedSprites::barrelFullRelativePath{ 
	L"Content\\Textures\\GameObjects\\Barrel.bmp" };
const std::wstring PredefinedSprites::characterFullRelativePath{ 
	L"Content\\Textures\\GameObjects\\Character.bmp" };

std::vector<std::shared_ptr<Sprite>> PredefinedSprites::m_sprites;
StaticConstructor PredefinedSprites::m_constructor(Construct);

std::shared_ptr<Sprite> PredefinedSprites::GetSprite(const std::wstring& spriteFullRelativePath) NOEXCEPT_WHEN_NDEBUG
{
	auto spriteIterator{ std::find_if(m_sprites.begin(), m_sprites.end(), 
		[&spriteFullRelativePath](const std::shared_ptr<Sprite>& sprite)
		{
			return sprite->GetFullRelativePath() == spriteFullRelativePath;
		}) };

	assert(spriteIterator != m_sprites.end());

	return *spriteIterator;
}

void PredefinedSprites::Construct() noexcept
{
	m_sprites.push_back(std::make_shared<Sprite>(wallFullRelativePath));
	m_sprites.push_back(std::make_shared<Sprite>(roadFullRelativePath));
	m_sprites.push_back(std::make_shared<Sprite>(crossFullRelativePath));
	m_sprites.push_back(std::make_shared<Sprite>(barrelFullRelativePath));
	m_sprites.push_back(std::make_shared<Sprite>(characterFullRelativePath));
}
