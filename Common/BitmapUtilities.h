#pragma once
#include "WinapiException.h"

namespace BitmapUtilities
{
	HBITMAP LoadBMP(const std::wstring& relativeFullPath);
	void UnloadBMP(HBITMAP sprite);
}
