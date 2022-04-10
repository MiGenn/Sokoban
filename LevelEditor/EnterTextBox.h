#pragma once
#include "Window.h"
#include "CustomDialogBox.h"

class EnterTextBox : public CustomDialogBox
{
public:
	EnterTextBox(const Window* parent);
	EnterTextBox(const EnterTextBox&) = delete;

	EnterTextBox& operator=(const EnterTextBox&) = delete;

	const std::wstring& GetText() const noexcept;
	bool IsCancelButtonPressed() const noexcept;
	bool IsOKButtonPressed() const noexcept;

private:
	bool m_isCancelButtonPressed{ false };
	std::wstring m_enteredText;

	INT_PTR HandleMessage(UINT message, WPARAM wParam, LPARAM lParam) override;

	void OnCommand(int controlID, int controlNotificationCode);
	void OnOKButton();
	void OnCancelButton();

	std::wstring ParseEnterTextControl() const noexcept;
};
