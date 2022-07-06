#include "StandardFileBox.h"

#include "CstringUtilities.h"
#include "PathUtilities.h"

#define THROW_IF_DIALOG_BOX_EXCEPTION if (CommDlgExtendedError()) throw WINAPI_EXCEPTION(CommDlgExtendedError())

StandardFileBox::StandardFileBox(const Window* parent, const std::wstring& initialPath, const wchar_t* filter,
	Type type, Flag flags, const std::wstring& defaultFileFullName, const std::wstring& boxTitle)
{
	wchar_t fileFullPathBuffer[MAX_PATH];
	wcsncpy_s(fileFullPathBuffer, defaultFileFullName.c_str(), MAX_PATH);

	OPENFILENAME fileCriterias{};
	fileCriterias.lStructSize = sizeof(OPENFILENAME);
	fileCriterias.hwndOwner = parent ? parent->GetHandle() : nullptr;
	fileCriterias.lpstrFilter = filter;
	fileCriterias.lpstrFile = fileFullPathBuffer;
	fileCriterias.nMaxFile = MAX_PATH;
	fileCriterias.lpstrInitialDir = initialPath.c_str();
	fileCriterias.lpstrTitle = boxTitle.empty() ? nullptr : boxTitle.c_str();
	fileCriterias.Flags = (int)flags;

	decltype(&GetOpenFileName) showBoxFunction =
		type == Type::Open ? GetOpenFileName : GetSaveFileName;
	if (showBoxFunction(&fileCriterias))
	{
		m_isOKButtonPressed = true;
		m_fileFullPath = fileCriterias.lpstrFile;
	}
	else
	{
		THROW_IF_DIALOG_BOX_EXCEPTION;
	}
}

const std::wstring& StandardFileBox::GetFileFullPath() const noexcept
{
    return m_fileFullPath;
}

bool StandardFileBox::IsOKButtonPressed() const noexcept
{
    return m_isOKButtonPressed;
}

bool StandardFileBox::IsCancelButtonPressed() const noexcept
{
    return !m_isOKButtonPressed;
}
