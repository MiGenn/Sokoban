#include "QuestionBox.h"

QuestionBox::QuestionBox(const Window* parent, const std::wstring& text) noexcept
{
	HWND parentHandle{ nullptr };
	if (parent)
		parentHandle = parent->GetHandle();

	auto pressedButtoID{ MessageBox(parentHandle, text.c_str(), L"Question", MB_OKCANCEL | MB_ICONQUESTION)};
	if (pressedButtoID == IDCANCEL)
		m_isCancelButtonPressed = true;
}

bool QuestionBox::IsCancelButtonPressed() const noexcept
{
	return m_isCancelButtonPressed;
}

bool QuestionBox::IsOKButtonPressed() const noexcept
{
	return !m_isCancelButtonPressed;
}
