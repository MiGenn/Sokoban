#include "CstringUntilities.h"

#include <string>

errno_t _cdecl CstringUntilities::wcscpy_s(wchar_t* destination,
	rsize_t destinationSizeInWords, int destinationShift, const wchar_t* source)
{
	rsize_t sizeWithShift{ destinationSizeInWords - destinationShift };
	return ::wcscpy_s(&destination[destinationShift], sizeWithShift, source);
}
