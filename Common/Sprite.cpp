#include "Sprite.h"

#include <cassert>
#include "BitmapProvider.h"
#include "Serializers.h"

Sprite::Sprite(const std::wstring& fullPath) :
	m_fullPath(fullPath)
{
	InitializeBitmap();
}

Sprite::Sprite(const Sprite& sprite) noexcept
{
	(*this) = sprite;
}

Sprite::Sprite(Sprite&& sprite) noexcept
{
	(*this) = std::move(sprite);
}

Sprite& Sprite::operator=(const Sprite& right) noexcept
{
	m_fullPath = right.m_fullPath;
	m_bitmap = BitmapProvider::GetBitmap(m_fullPath);

	return *this;
}

Sprite& Sprite::operator=(Sprite&& right) noexcept
{
	m_fullPath = std::move(right.m_fullPath);
	m_bitmap = right.m_bitmap;
	right.m_bitmap = nullptr;

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
	return !m_bitmap;
}

void Sprite::SerializeIDToOpenedFile(std::ofstream& file) const
{
	IBinarySerializable::SerializeIDToOpenedFile<Sprite>(file);
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
	m_bitmap = BitmapProvider::GetBitmap(m_fullPath);
}
