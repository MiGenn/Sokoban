#include "BitmapProvider.h"

#include "BitmapUtilities.h"

std::unordered_map<std::wstring, HBITMAP> BitmapProvider::m_bitmaps;

HBITMAP BitmapProvider::GetBitmap(const std::wstring& tileSetRelativeFullPath)
{
	auto pathAndBitmapIterator{ m_bitmaps.find(tileSetRelativeFullPath) };
	if (pathAndBitmapIterator == m_bitmaps.end())
		pathAndBitmapIterator = m_bitmaps.emplace(tileSetRelativeFullPath, 
			Utilities::Winapi::Bitmap::LoadBMP(tileSetRelativeFullPath)).first;

	return pathAndBitmapIterator->second;
}
