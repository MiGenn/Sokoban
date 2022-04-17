#pragma once
#include <unordered_map>
#include "WinapiException.h"

class BitmapManager
{
public:

	BitmapManager() = delete;
	BitmapManager(const BitmapManager&) = delete;

	BitmapManager& operator=(const BitmapManager&) = delete;

	static HBITMAP GetBitmap(const std::wstring& fullPath);

private:
	std::unordered_map<std::wstring, HBITMAP> m_bitmaps;
};
