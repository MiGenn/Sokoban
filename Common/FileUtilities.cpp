#include "FileUtilities.h"

bool FileUtilities::IsPathValid(const std::wstring& fileFullPath) noexcept
{
    struct _stat fileInfo;
    return _wstat(fileFullPath.c_str(), &fileInfo) != -1;
}
