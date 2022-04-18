#pragma once
#include <unordered_map>
#include "WinapiException.h"

class BitmapManager
{
public:

	BitmapManager() = delete;
	BitmapManager(const BitmapManager&) = delete;

	BitmapManager& operator=(const BitmapManager&) = delete;

	static const std::pair<std::wstring, HBITMAP>& GetBitmap(const std::wstring& fullPath);

private:
	static std::unordered_map<std::wstring, HBITMAP> m_bitmaps;
};
