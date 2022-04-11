#include "SelectFileBox.h"

#include <commdlg.h>
#include "CstringUntilities.h"
#include "PathUtilities.h"

#pragma comment(lib, "comdlg32")
#define THROW_IF_DIALOG_BOX_EXCEPTION if (CommDlgExtendedError()) throw WINAPI_EXCEPTION(CommDlgExtendedError());

SelectFileBox::SelectFileBox(const Window* parent, const std::wstring& initialPath, 
	const std::pair<std::wstring, std::wstring>& descriptionAndfilter) :
	m_parent(parent), m_initialPath(initialPath)
{
	static constexpr int terminatingZerosCount{ 3 };
	int filterSize{ (int)descriptionAndfilter.first.size() + 
		(int)descriptionAndfilter.second.size() + terminatingZerosCount };

	m_filter = new wchar_t[filterSize];
	m_filter[filterSize - 1] = L'\0';
	wcscpy_s(m_filter, filterSize, descriptionAndfilter.first.c_str());
	CstringUntilities::wcscpy_s(m_filter, filterSize,
		(int)descriptionAndfilter.first.size() + 1, descriptionAndfilter.second.c_str());
	
	StartSelecting();
}

SelectFileBox::~SelectFileBox() noexcept
{
	delete[] m_filter;
}

void SelectFileBox::StartSelecting()
{
	HWND parentHandle{ NULL };
	if (m_parent)
		parentHandle = m_parent->GetHandle();

	wchar_t fileFullPathBuffer[MAX_PATH];
	fileFullPathBuffer[0] = L'\0';

	OPENFILENAME openFileName{};
	openFileName.lStructSize = sizeof(OPENFILENAME);
	openFileName.hwndOwner = parentHandle;
	openFileName.lpstrFilter = m_filter;
	openFileName.lpstrFile = (LPWSTR)fileFullPathBuffer;
	openFileName.nMaxFile = MAX_PATH;
	openFileName.lpstrInitialDir = m_initialPath.c_str();

	if (GetOpenFileName(&openFileName))
	{
		m_isFileSelected = true;
		m_fileFullPath = openFileName.lpstrFile;
		m_filePath = PathUtilities::ExtractPath(m_fileFullPath);
		m_fileFullName = PathUtilities::ExtractFullName(m_fileFullPath);
	}
	else
	{
		THROW_IF_DIALOG_BOX_EXCEPTION;
	}
}

const std::wstring& SelectFileBox::GetFileFullPath() const noexcept
{
	return m_fileFullPath;
}

const std::wstring& SelectFileBox::GetFilePath() const noexcept
{
	return m_filePath;
}

const std::wstring& SelectFileBox::GetFileFullName() const noexcept
{
	return m_fileFullName;
}

bool SelectFileBox::IsFileSelected() const noexcept
{
	return m_isFileSelected;
}
