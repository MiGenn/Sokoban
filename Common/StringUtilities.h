#pragma once
#include <string>

namespace Utilities::Cpp::String
{
	static const std::wstring empty;

	std::wstring DeleteFirstAndLastSymbols(const std::wstring& string) noexcept;
};
