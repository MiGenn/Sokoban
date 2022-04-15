#pragma once
#include <string>

class IFileBox
{
public:
	IFileBox() noexcept = default;
	IFileBox(const IFileBox&) = delete;

	IFileBox& operator=(const IFileBox&) = delete;

	virtual const std::wstring& GetFileFullPath() const noexcept = 0;

	virtual bool IsOKButtonPressed() const noexcept = 0;
	virtual bool IsCancelButtonPressed() const noexcept = 0;
};
