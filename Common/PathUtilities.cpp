#include "PathUtilities.h"

#include "WinapiException.h"

std::wstring PathUtilities::ExtractPath(const std::wstring& fullPath)
{
    wchar_t pathBuffer[MAX_PATH];
    _wsplitpath_s(fullPath.c_str(), nullptr, 0, pathBuffer, MAX_PATH, nullptr, 0, nullptr, 0);

    return { pathBuffer };
}

std::wstring PathUtilities::ExtractName(const std::wstring& fullPath)
{
    static constexpr int nameBufferSize{ 64 };
    wchar_t nameBuffer[nameBufferSize];
    _wsplitpath_s(fullPath.c_str(), nullptr, 0, nullptr, 0, nameBuffer, nameBufferSize, nullptr, 0);

    return { nameBuffer };
}

std::wstring PathUtilities::ExtractExtension(const std::wstring& fullPath)
{
    static constexpr int extensionBufferSize{ 32 };
    wchar_t extensionBuffer[extensionBufferSize];
    _wsplitpath_s(fullPath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, extensionBuffer, extensionBufferSize);

    return { extensionBuffer };
}

std::wstring PathUtilities::ExtractFullName(const std::wstring& fullPath)
{
    return ExtractName(fullPath) + ExtractExtension(fullPath);
}
