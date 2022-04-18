#include "Sprite.h"

#include <cassert>
#include "BitmapManager.h"
#include "Serializers.h"

Sprite::Sprite(const std::wstring& fullPath)
{
	Initialize(fullPath);
}

Sprite::Sprite(Sprite&& sprite) noexcept
{
	(*this) = std::move(sprite);
}

Sprite& Sprite::operator=(Sprite&& right) noexcept
{
	m_fullPath = right.m_fullPath;
	m_bitmap = right.m_bitmap;
	right.m_fullPath = &StringUtilities::empty;
	right.m_bitmap = NULL;

	return *this;
}

const std::wstring& Sprite::GetFullRelativePath() const noexcept
{
	return *m_fullPath;
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
	WstringBinarySerializer::SerializeToOpenedFile(*m_fullPath, file);
}

void Sprite::DeserializeFromOpenedFileToSelf(std::ifstream& file)
{
	std::wstring fullRelativePath;
	WstringBinarySerializer::DeserializeFromOpenedFile(fullRelativePath, file);
	Initialize(fullRelativePath);
}

void Sprite::Initialize(const std::wstring& fullPath)
{
	auto& pathAndBitmap{ BitmapManager::GetBitmap(fullPath) };
	m_fullPath = &pathAndBitmap.first;
	m_bitmap = pathAndBitmap.second;
}
