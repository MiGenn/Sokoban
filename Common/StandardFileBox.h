#pragma once
#include "IFileBox.h"
#include "Window.h"

class StandardFileBox final : public IFileBox
{
public:
	enum class Type
	{
		Open,
		Save
	};

	enum class Flag
	{
		OverwritePrompt = OFN_OVERWRITEPROMPT
	};

	StandardFileBox(const Window* parent, const std::wstring& initialPath, const wchar_t* filter, 
		Type type, Flag flag = Flag::OverwritePrompt, 
		const std::wstring& defaultFileFullName = L"", const std::wstring& boxTitle = L"");
	StandardFileBox(const StandardFileBox&) = delete;

	StandardFileBox& operator=(const StandardFileBox&) = delete;

	const std::wstring& GetFileFullPath() const noexcept override;

	bool IsOKButtonPressed() const noexcept override;
	bool IsCancelButtonPressed() const noexcept override;

private:
	bool m_isOKButtonPressed{ false };
	std::wstring m_fileFullPath;
};
