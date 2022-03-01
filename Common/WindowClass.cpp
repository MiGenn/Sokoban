#include "WindowClass.h"

const wchar_t* WindowClass::GetName() const
{
	return m_name;
}

WindowClass::WindowClass(const wchar_t* name) :
	m_name(name)
{

}

WindowClass::~WindowClass()
{
	UnregisterClass(m_name, GetModuleHandle(nullptr));
}

LRESULT WindowClass::SetupMessageHandling(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_NCCREATE)
	{
		const auto const createStruct{ reinterpret_cast<CREATESTRUCT*>(lParam) };
		auto const window{ reinterpret_cast<Window*>(createStruct->lpCreateParams) };

		SetWindowLongPtr(handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		SetWindowLongPtr(handle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(RouteMessages));

		return RouteMessages(handle, message, wParam, lParam);
	}

	return DefWindowProc(handle, message, wParam, lParam);
}

LRESULT WindowClass::RouteMessages(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	auto const window{ reinterpret_cast<Window*>(GetWindowLongPtr(handle, GWLP_USERDATA)) };
	window->m_handle = handle;

	return window->HandleMessages(message, wParam, lParam);
}