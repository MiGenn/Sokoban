#include "EnterTextBox.h"

#include "EditorResourceMacros.h"

EnterTextBox::EnterTextBox(const Window* parent, const std::wstring& hintText) noexcept :
	CustomDialogBox(parent), m_hintText(hintText)
{
	HWND parentHandle{ nullptr };
	if (parent)
		parentHandle = parent->GetHandle();

	DialogBoxParam(nullptr, MAKEINTRESOURCE(IDD_ENTER_TEXT_BOX),
		parentHandle, SetupMessageHandling, reinterpret_cast<LPARAM>(this));
}

const std::wstring& EnterTextBox::GetText() const noexcept
{
	return m_enteredText;
}

bool EnterTextBox::IsCancelButtonPressed() const noexcept
{
	return m_isCancelButtonPressed;
}

bool EnterTextBox::IsOKButtonPressed() const noexcept
{
	return !m_isCancelButtonPressed;
}

INT_PTR EnterTextBox::HandleMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		OnInit();
		return true;

	case WM_HOTKEY:
		OnHotKey((HotKey)wParam);
		return true;

	case WM_COMMAND:
		OnCommand(LOWORD(wParam), HIWORD(wParam));
		return true;
	}

	return false;
}

void EnterTextBox::OnInit()
{
	auto hintTextHandle{ GetDlgItem(m_handle, ID_ENTER_TEXT_TEXT) };
	SetWindowText(hintTextHandle, m_hintText.c_str());

	RegisterHotKey(m_handle, (int)HotKey::Enter, NULL, VK_RETURN);
	RegisterHotKey(m_handle, (int)HotKey::Escape, NULL, VK_ESCAPE);
}

void EnterTextBox::OnCommand(int controlID, int controlNotificationID)
{
	switch (controlID)
	{
	case IDC_ENTER_TEXT_OK_BUTTON:
		if (controlNotificationID == BN_CLICKED)
			OnOKButton();
		break;

	case IDC_ENTER_TEXT_CANCEL_BUTTON:
		if (controlNotificationID == BN_CLICKED)
			OnCancelButton();
		break;
	}
}

void EnterTextBox::OnHotKey(HotKey hotKey)
{
	switch (hotKey)
	{
	case HotKey::Enter:
		OnOKButton();
		break;

	case HotKey::Escape:
		OnCancelButton();
		break;
	}
}

void EnterTextBox::OnOKButton()
{
	m_enteredText = ParseEnterTextControl();
	EndDialog(m_handle, true);
}

void EnterTextBox::OnCancelButton()
{
	m_isCancelButtonPressed = true;
	EndDialog(m_handle, true);
}

std::wstring EnterTextBox::ParseEnterTextControl() const noexcept
{
	static constexpr int fileNameMaxSize{ 64 };
	wchar_t fileNameBuffer[fileNameMaxSize];
	auto editControlHandle{ GetDlgItem(m_handle, IDC_ENTER_TEXT_EDIT) };
	GetWindowText(editControlHandle, fileNameBuffer, fileNameMaxSize);

	return { fileNameBuffer };
}
