#include "BitmapProvider.h"

#include "BitmapUtilities.h"

std::unordered_map<std::wstring, HBITMAP> BitmapProvider::m_bitmaps;

HBITMAP BitmapProvider::GetBitmap(const std::wstring& relativeFullPath)
{
	auto pathAndBitmapIterator{ m_bitmaps.find(relativeFullPath) };
	if (pathAndBitmapIterator == m_bitmaps.end())
		pathAndBitmapIterator = m_bitmaps.emplace(relativeFullPath, Utilities::Winapi::Bitmap::LoadBMP(relativeFullPath)).first;

	return pathAndBitmapIterator->second;
}
