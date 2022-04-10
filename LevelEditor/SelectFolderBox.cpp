#include "SelectFolderBox.h"

#include <shlobj_core.h>
#include "Window.h"

SelectFolderBox::SelectFolderBox(const Window* parent) :
	m_parent(parent)
{
	StartSelecting();
}

void SelectFolderBox::StartSelecting()
{
	HWND parentHandle{ NULL };
	if (m_parent)
		parentHandle = m_parent->GetHandle();

	BROWSEINFOW browseInfo{};
	browseInfo.hwndOwner = parentHandle;
	browseInfo.ulFlags = BIF_USENEWUI;

	auto selectedFolder{ SHBrowseForFolder(&browseInfo) };
	if (!selectedFolder)
	{
		m_isAnyFolderSelected = false;
		m_folderFullPath.clear();
		m_folderFullPathWithTrailingBackslash.clear();
		return;
	}

	m_isAnyFolderSelected = true;
	wchar_t folderFullPathBuffer[MAX_PATH];
	SHGetPathFromIDList(selectedFolder, folderFullPathBuffer);
	m_folderFullPath = folderFullPathBuffer;
	m_folderFullPathWithTrailingBackslash = m_folderFullPath;
	m_folderFullPathWithTrailingBackslash.append(L"\\");

	ILFree(selectedFolder);
}

const std::wstring& SelectFolderBox::GetFolderFullPath() const noexcept
{
	return m_folderFullPath;
}

const std::wstring& SelectFolderBox::GetFolderFullPathWithTrailingBackslash() const noexcept
{
	return m_folderFullPathWithTrailingBackslash;
}

bool SelectFolderBox::IsFolderSelected() const noexcept
{
	return m_isAnyFolderSelected;
}
