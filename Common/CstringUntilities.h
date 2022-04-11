#pragma once
#include <errno.h>

namespace CstringUntilities
{
	errno_t _cdecl wcscpy_s(wchar_t* destination,
		rsize_t destinationSizeInWords, int destinationShift, const wchar_t* source);
};
