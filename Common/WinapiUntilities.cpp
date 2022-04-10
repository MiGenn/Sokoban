#include "WinapiUntilities.h"

#include <algorithm>
#include "PathUtilities.h"

std::wstring WinapiUntilities::GetModulePath(HMODULE moduleHandle)
{
    wchar_t fullPathBuffer[MAX_PATH];
    GetModuleFileName(moduleHandle, fullPathBuffer, MAX_PATH);

    return PathUtilities::ExtractPath(fullPathBuffer);
}
