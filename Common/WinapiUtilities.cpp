#include "WinapiUtilities.h"

#include <algorithm>
#include "PathUtilities.h"

std::wstring Utilities::Winapi::GetModulePath(HMODULE moduleHandle)
{
    wchar_t fullPathBuffer[MAX_PATH];
    GetModuleFileName(moduleHandle, fullPathBuffer, MAX_PATH);

    return Utilities::Cpp::Path::ExtractPath(fullPathBuffer);
}

HWND Utilities::Winapi::FindMenuWindow(HWND parent)
{
    return FindWindowEx(parent, NULL, MAKEINTATOM(0x8000), NULL);
}
