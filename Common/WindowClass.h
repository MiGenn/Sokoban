#pragma once
#include "Window.h"
#include "BuildInfo.h"

class WindowClass
{
public:
	const wchar_t* GetName() const noexcept;

protected:
	WindowClass(const wchar_t* name) NOEXCEPT_WHEN_NDEBUG;
	WindowClass(const WindowClass&) = delete;
	virtual ~WindowClass() noexcept;

	WindowClass& operator=(const WindowClass&) = delete;

	static LRESULT SetupMessageHandling(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

private:
	const wchar_t* const m_name;

	static LRESULT RouteMessage(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
};
