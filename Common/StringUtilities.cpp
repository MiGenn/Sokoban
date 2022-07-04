#include "StringUtilities.h"

std::wstring Utilities::Cpp::String::DeleteFirstAndLastSymbols(const std::wstring& string)
{
	if (string.size() <= 2ul)
		return empty;

	return string.substr(1ul, string.size() - 2ul);
}
