#pragma once
#include "Window.h"

class WindowClass
{
public:
	const wchar_t* GetName() const;

protected:
	WindowClass(const wchar_t* name);
	WindowClass(const WindowClass&) = delete;
	WindowClass& operator=(const WindowClass&) = delete;
	virtual ~WindowClass();

	static LRESULT SetupMessageHandling(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

private:
	const wchar_t* const m_name;

	static LRESULT RouteMessages(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
};
