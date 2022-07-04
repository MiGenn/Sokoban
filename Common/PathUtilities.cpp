#include "PathUtilities.h"

#include "WinapiException.h"

std::wstring Utilities::Cpp::Path::ExtractPath(const std::wstring& fullPath)
{
    static constexpr int driveDesignatorSize{ 3 };

    wchar_t pathBuffer[MAX_PATH];
    _wsplitpath_s(fullPath.c_str(), pathBuffer, driveDesignatorSize, 
        &pathBuffer[driveDesignatorSize - 1], MAX_PATH - driveDesignatorSize - 1, nullptr, 0, nullptr, 0);

    return { pathBuffer };
}

std::wstring Utilities::Cpp::Path::ExtractName(const std::wstring& fullPath)
{
    static constexpr int nameBufferSize{ 64 };
    wchar_t nameBuffer[nameBufferSize];
    _wsplitpath_s(fullPath.c_str(), nullptr, 0, nullptr, 0, nameBuffer, nameBufferSize, nullptr, 0);

    return { nameBuffer };
}

std::wstring Utilities::Cpp::Path::ExtractExtension(const std::wstring& fullPath)
{
    static constexpr int extensionBufferSize{ 32 };
    wchar_t extensionBuffer[extensionBufferSize];
    _wsplitpath_s(fullPath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, extensionBuffer, extensionBufferSize);

    return { extensionBuffer };
}

std::wstring Utilities::Cpp::Path::ExtractFullName(const std::wstring& fullPath)
{
    return ExtractName(fullPath) + ExtractExtension(fullPath);
}
