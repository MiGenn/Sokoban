#include "CustomDialogBox.h"

CustomDialogBox::CustomDialogBox(const Window* parent) noexcept :
    m_parent(parent)
{

}

INT_PTR CustomDialogBox::SetupMessageHandling(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_INITDIALOG)
	{
		auto customDialogBox{ reinterpret_cast<CustomDialogBox*>(lParam) };
		SetWindowLongPtr(handle, DWLP_USER, reinterpret_cast<LONG_PTR>(customDialogBox));
		SetWindowLongPtr(handle, DWLP_DLGPROC, reinterpret_cast<LONG_PTR>(RouteMessage));

		return RouteMessage(handle, message, wParam, lParam);
	}

	return false;
}

INT_PTR CustomDialogBox::RouteMessage(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	auto customDialogBox{ reinterpret_cast<CustomDialogBox*>(GetWindowLongPtr(handle, DWLP_USER)) };
	customDialogBox->m_handle = handle;

	customDialogBox->HandleMessage(message, wParam, lParam);

	return false;
}
