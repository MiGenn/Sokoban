#include "SelectFolderBox.h"

SelectFolderBox::SelectFolderBox(const Window* parent)
{
	BROWSEINFOW browseInfo{};
	browseInfo.hwndOwner = parent ? parent->GetHandle() : NULL;
	browseInfo.ulFlags = BIF_USENEWUI;

	auto selectedFolder{ SHBrowseForFolder(&browseInfo) };
	if (selectedFolder)
	{
		m_isFolderSelected = true;
		wchar_t folderFullPathBuffer[MAX_PATH];
		SHGetPathFromIDList(selectedFolder, folderFullPathBuffer);
		m_folderFullPathWithTrailingBackslash = folderFullPathBuffer;
		m_folderFullPathWithTrailingBackslash.append(L"\\");
		m_folderFullPath = m_folderFullPathWithTrailingBackslash;
		m_folderFullPath.remove_suffix(1);

		ILFree(selectedFolder);
	}
}

std::wstring_view SelectFolderBox::GetFolderFullPath() const noexcept
{
	return m_folderFullPath;
}

const std::wstring& SelectFolderBox::GetFolderFullPathWithTrailingBackslash() const noexcept
{
	return m_folderFullPathWithTrailingBackslash;
}

bool SelectFolderBox::IsFolderSelected() const noexcept
{
	return m_isFolderSelected;
}
