#pragma once
#include "WinapiException.h"

namespace Utilities::Winapi::Bitmap
{
	HBITMAP LoadBMP(const std::wstring& fullPath);
	void UnloadBMP(HBITMAP sprite);
}
