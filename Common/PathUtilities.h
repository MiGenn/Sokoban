#pragma once
#include <string>

namespace Utilities::Cpp::Path
{
	std::wstring ExtractPath(const std::wstring& fullPath);
	std::wstring ExtractName(const std::wstring& fullPath);
	std::wstring ExtractExtension(const std::wstring& fullPath);
	std::wstring ExtractFullName(const std::wstring& fullPath);

	bool IsPathValid(const std::wstring& fileFullPath) noexcept;
}
