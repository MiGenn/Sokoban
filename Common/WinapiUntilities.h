#pragma once
#include "WinapiException.h"

namespace WinapiUntilities
{
	std::wstring GetModulePath(HMODULE moduleHandle);
	HWND FindMenuWindow(HWND parent);
}
