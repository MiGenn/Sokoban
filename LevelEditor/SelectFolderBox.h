#pragma once
#include "WinapiException.h"

class SelectFolderBox
{
public:
	SelectFolderBox(const class Window* parent);
	SelectFolderBox(const SelectFolderBox&) = delete;

	SelectFolderBox& operator=(const SelectFolderBox&) = delete;

	void StartSelecting();

	const std::wstring& GetFolderFullPath() const noexcept;
	const std::wstring& GetFolderFullPathWithTrailingBackslash() const noexcept;
	bool IsFolderSelected() const noexcept;

private:
	const Window* m_parent;

	std::wstring m_folderFullPath;
	std::wstring m_folderFullPathWithTrailingBackslash;
	bool m_isFolderSelected{ false };
};
