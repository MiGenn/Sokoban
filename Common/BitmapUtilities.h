#pragma once
#include "WinapiException.h"

namespace BitmapUtilities
{
	HBITMAP LoadBMP(const std::wstring& fullPath);
	void UnloadBMP(HBITMAP sprite);
}
