#include "Sprites.h"

#include <cassert>
#include "BitmapUtilities.h"
#include "Sprite.h"


const std::wstring Sprites::wallFullRelativePath{ 
	L"Content\\Textures\\GameObjects\\Wall.bmp" };
const std::wstring Sprites::roadFullRelativePath{ 
	L"Content\\Textures\\GameObjects\\Road.bmp" };
const std::wstring Sprites::crossFullRelativePath{ 
	L"Content\\Textures\\GameObjects\\Cross.bmp" };
const std::wstring Sprites::barrelFullRelativePath{ 
	L"Content\\Textures\\GameObjects\\Barrel.bmp" };
const std::wstring Sprites::characterFullRelativePath{ 
	L"Content\\Textures\\GameObjects\\Character.bmp" };

Sprite Sprites::GetSprite(const std::wstring& spriteFullRelativePath) NOEXCEPT_WHEN_NDEBUG
{
	return { spriteFullRelativePath };
}

std::unordered_map<std::wstring, HBITMAP> Sprites::m_sprites;
StaticConstructor Sprites::m_constructor(Construct);

HBITMAP Sprites::GetRawSprite(const std::wstring& spriteFullRelativePath) NOEXCEPT_WHEN_NDEBUG
{
	auto spriteIterator{ m_sprites.find(spriteFullRelativePath) };
	assert(spriteIterator != m_sprites.end());

	return spriteIterator->second;
}

void Sprites::Construct() noexcept
{
	m_sprites.emplace(wallFullRelativePath, 
		BitmapUtilities::LoadBMP(wallFullRelativePath));
	m_sprites.emplace(roadFullRelativePath, 
		BitmapUtilities::LoadBMP(roadFullRelativePath));
	m_sprites.emplace(crossFullRelativePath, 
		BitmapUtilities::LoadBMP(crossFullRelativePath));
	m_sprites.emplace(barrelFullRelativePath, 
		BitmapUtilities::LoadBMP(barrelFullRelativePath));
	m_sprites.emplace(characterFullRelativePath, 
		BitmapUtilities::LoadBMP(characterFullRelativePath));
}
