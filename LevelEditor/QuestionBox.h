#pragma once
#include "Window.h"

class QuestionBox final
{
public:
	QuestionBox(const Window* parent, const std::wstring& text) noexcept;
	QuestionBox(const QuestionBox&) = delete;

	QuestionBox& operator=(const QuestionBox&) = delete;

	bool IsCancelButtonPressed() const noexcept;
	bool IsOKButtonPressed() const noexcept;

private:
	bool m_isCancelButtonPressed{ false };
};
