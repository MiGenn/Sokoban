#include "BitmapProvider.h"

#include "BitmapUtilities.h"

std::unordered_map<std::wstring, HBITMAP> BitmapProvider::m_bitmaps;

HBITMAP BitmapProvider::GetBitmap(const std::wstring& fullPath)
{
	auto pathAndBitmapIterator{ m_bitmaps.find(fullPath) };
	if (pathAndBitmapIterator == m_bitmaps.end())
		pathAndBitmapIterator = m_bitmaps.emplace(fullPath, Utilities::Winapi::Bitmap::LoadBMP(fullPath)).first;

	return pathAndBitmapIterator->second;
}
