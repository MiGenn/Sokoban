#pragma once
#include <string>

namespace PathUtilities
{
	std::wstring ExtractPath(const std::wstring& fullPath);
	std::wstring ExtractName(const std::wstring& fullPath);
	std::wstring ExtractExtension(const std::wstring& fullPath);
	std::wstring ExtractFullName(const std::wstring& fullPath);
}
