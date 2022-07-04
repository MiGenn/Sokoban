#pragma once
#include <concepts>
#include <wil/resource.h>

namespace Utilities::Winapi::SmartPointer
{
	template <typename T>
	concept GDIOBJ = std::same_as<HGDIOBJ, T> || std::same_as<HPEN, T> || std::same_as<HBRUSH, T> ||
		std::same_as<HFONT, T> || std::same_as<HBITMAP, T> || std::same_as<HPALETTE, T> || std::same_as<HRGN, T>;

	template <GDIOBJ T>
	using UniqueGDIOBJ = wil::unique_any<T, decltype(&DeleteObject), DeleteObject>;
}
