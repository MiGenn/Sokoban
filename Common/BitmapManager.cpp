#include "BitmapManager.h"

#include "BitmapUtilities.h"

std::unordered_map<std::wstring, HBITMAP> BitmapManager::m_bitmaps;

const std::pair<std::wstring, HBITMAP>& BitmapManager::GetBitmap(const std::wstring& fullPath)
{
	auto pathAndBitmapIterator{ m_bitmaps.find(fullPath) };
	if (pathAndBitmapIterator == m_bitmaps.end())
		pathAndBitmapIterator = m_bitmaps.emplace(fullPath, BitmapUtilities::LoadBMP(fullPath)).first;

	return *pathAndBitmapIterator;
}
