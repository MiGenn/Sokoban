#pragma once
#include "CustomDialogBox.h"

class EnterTextBox : public CustomDialogBox
{
public:
	EnterTextBox(const Window* parent, const std::wstring& hintText);
	EnterTextBox(const EnterTextBox&) = delete;

	EnterTextBox& operator=(const EnterTextBox&) = delete;

	const std::wstring& GetText() const noexcept;
	bool IsCancelButtonPressed() const noexcept;
	bool IsOKButtonPressed() const noexcept;

private:
	enum class HotKey
	{
		Enter,
		Escape
	};

	const std::wstring hintText;

	bool m_isCancelButtonPressed{ false };
	std::wstring m_enteredText;

	INT_PTR HandleMessage(UINT message, WPARAM wParam, LPARAM lParam) override;

	void OnInit();
	void OnCommand(int controlID, int controlNotificationCode);
	void OnHotKey(HotKey hotKey);

	void OnOKButton();
	void OnCancelButton();

	std::wstring ParseEnterTextControl() const noexcept;
};
