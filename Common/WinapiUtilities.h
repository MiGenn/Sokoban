#pragma once
#include "WinapiException.h"

namespace Utilities::Winapi
{
	std::wstring GetModulePath(HMODULE moduleHandle);
	HWND FindMenuWindow(HWND parent) noexcept;
}
