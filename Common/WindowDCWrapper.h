#pragma once
#include "Window.h"

class WindowDCWrapper final
{
public:
	WindowDCWrapper(const Window* window) NOEXCEPT_WHEN_NDEBUG;
	WindowDCWrapper(const WindowDCWrapper&) = delete;
	~WindowDCWrapper() noexcept;

	WindowDCWrapper& operator=(const WindowDCWrapper&) = delete;

	HDC Get() const noexcept;

private:
	const Window* const m_window;
	const HDC m_windowContext;
};
