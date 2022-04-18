#pragma once
#include <string>

namespace StringUtilities
{
	static const std::wstring empty;

	std::wstring DeleteQuotationMarks(const std::wstring& string);
};
