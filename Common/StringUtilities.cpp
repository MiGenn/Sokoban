#include "StringUtilities.h"

std::wstring StringUtilities::DeleteQuotationMarks(const std::wstring& string)
{
	if (string.size() <= 2)
		return empty;

	return string.substr(1, string.size() - 2);
}
