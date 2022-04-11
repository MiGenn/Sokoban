#pragma once
#include "Window.h"

class SelectFileBox
{
public:
	SelectFileBox(const Window* parent, const std::wstring& initialPath,
		const std::pair<std::wstring, std::wstring>& descriptionAndfilter);
	SelectFileBox(const SelectFileBox&) = delete;
	~SelectFileBox() noexcept;

	SelectFileBox& operator=(const SelectFileBox&) = delete;

	void StartSelecting();

	const std::wstring& GetFileFullPath() const noexcept;
	const std::wstring& GetFilePath() const noexcept;
	const std::wstring& GetFileFullName() const noexcept;
	bool IsFileSelected() const noexcept;

private:
	const Window* m_parent;
	std::wstring m_initialPath;
	wchar_t* m_filter;

	bool m_isFileSelected{ false };
	std::wstring m_fileFullPath;
	std::wstring m_filePath;
	std::wstring m_fileFullName;
};
