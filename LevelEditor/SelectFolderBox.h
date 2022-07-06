#pragma once
#include <string_view>
#include "Window.h"

class SelectFolderBox final
{
public:
	SelectFolderBox(const Window* parent) noexcept;
	SelectFolderBox(const SelectFolderBox&) = delete;

	SelectFolderBox& operator=(const SelectFolderBox&) = delete;

	std::wstring_view GetFolderFullPath() const noexcept;
	const std::wstring& GetFolderFullPathWithTrailingBackslash() const noexcept;
	bool IsFolderSelected() const noexcept;

private:
	std::wstring_view m_folderFullPath;
	std::wstring m_folderFullPathWithTrailingBackslash;
	bool m_isFolderSelected{ false };
};
