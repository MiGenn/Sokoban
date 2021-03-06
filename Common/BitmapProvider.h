#pragma once
#include <unordered_map>
#include "WinapiException.h"

class BitmapProvider
{
public:
	BitmapProvider() = delete;
	BitmapProvider(const BitmapProvider&) = delete;

	BitmapProvider& operator=(const BitmapProvider&) = delete;

	static HBITMAP GetBitmap(const std::wstring& tileSetRelativeFullPath);

private:
	static std::unordered_map<std::wstring, HBITMAP> m_bitmaps;
};
