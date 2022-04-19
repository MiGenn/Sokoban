#include "Sprite.h"

#include <cassert>
#include "BitmapManager.h"
#include "Serializers.h"

Sprite::Sprite(const std::wstring& fullPath) :
	m_fullPath(fullPath)
{
	InitializeBitmap();
}

Sprite::Sprite(Sprite&& sprite) noexcept
{
	(*this) = std::move(sprite);
}

Sprite& Sprite::operator=(Sprite&& right) noexcept
{
	m_fullPath = std::move(right.m_fullPath);
	m_bitmap = right.m_bitmap;
	right.m_bitmap = NULL;

	return *this;
}

const std::wstring& Sprite::GetFullPath() const noexcept
{
	return m_fullPath;
}

HBITMAP Sprite::GetBitmap() const noexcept
{
	return m_bitmap;
}

bool Sprite::IsEmpty() const noexcept
{
	return m_bitmap == NULL;
}

void Sprite::SerializeToOpenedFile(std::ofstream& file) const
{
	WstringBinarySerializer::SerializeToOpenedFile(m_fullPath, file);
}

void Sprite::DeserializeFromOpenedFileToSelf(std::ifstream& file)
{
	WstringBinarySerializer::DeserializeFromOpenedFile(m_fullPath, file);
	InitializeBitmap();
}

void Sprite::InitializeBitmap()
{
	m_bitmap = BitmapManager::GetBitmap(m_fullPath);
}
