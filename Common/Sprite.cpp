#include "Sprite.h"

#include <cassert>
#include "Sprites.h"
#include "BitmapUtilities.h"
#include "Serializers.h"

Sprite::Sprite(const std::wstring& spriteFullRalativePath) NOEXCEPT_WHEN_NDEBUG :
	m_spriteFullRelativePath(spriteFullRalativePath)
{
	m_spriteBitmap = Sprites::GetRawSprite(spriteFullRalativePath);
}

Sprite::Sprite(Sprite&& sprite) noexcept
{
	(*this) = std::move(sprite);
}

Sprite& Sprite::operator=(Sprite&& right) noexcept
{
	m_spriteFullRelativePath = std::move(right.m_spriteFullRelativePath);
	m_spriteBitmap = right.m_spriteBitmap;
	right.m_spriteBitmap = NULL;

	return *this;
}

HBITMAP Sprite::GetBitmap() const noexcept
{
	return m_spriteBitmap;
}

bool Sprite::IsEmptyBitmap() const noexcept
{
	return m_spriteBitmap == NULL;
}

void Sprite::SerializeToOpenedFile(std::ofstream& file) const
{
	WstringBinarySerializer::SerializeToOpenedFile(m_spriteFullRelativePath, file);
}

void Sprite::DeserializeFromOpenedFileToSelf(std::ifstream& file)
{
	WstringBinarySerializer::DeserializeFromOpenedFile(m_spriteFullRelativePath, file);
	m_spriteBitmap = Sprites::GetRawSprite(m_spriteFullRelativePath);
}
