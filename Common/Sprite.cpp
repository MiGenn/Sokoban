#include "Sprite.h"

#include <cassert>
#include "BitmapUtilities.h"
#include "Serializers.h"

Sprite::Sprite(const std::wstring& fullRalativePath) :
	m_fullRelativePath(fullRalativePath)
{
	m_bitmap = BitmapUtilities::LoadBMP(m_fullRelativePath);
}

Sprite::Sprite(Sprite&& sprite) noexcept
{
	(*this) = std::move(sprite);
}

Sprite& Sprite::operator=(Sprite&& right) noexcept
{
	m_fullRelativePath = std::move(right.m_fullRelativePath);
	m_bitmap = right.m_bitmap;
	right.m_bitmap = NULL;

	return *this;
}

const std::wstring& Sprite::GetFullRelativePath() const noexcept
{
	return m_fullRelativePath;
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
	WstringBinarySerializer::SerializeToOpenedFile(m_fullRelativePath, file);
}

void Sprite::DeserializeFromOpenedFileToSelf(std::ifstream& file)
{
	WstringBinarySerializer::DeserializeFromOpenedFile(m_fullRelativePath, file);
	m_bitmap = BitmapUtilities::LoadBMP(m_fullRelativePath); ////////
}
