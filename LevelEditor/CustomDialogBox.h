#pragma once
#include "Window.h"

class CustomDialogBox
{
public:
	CustomDialogBox(const Window* parent);
	CustomDialogBox(const CustomDialogBox&) = delete;

	CustomDialogBox& operator=(const CustomDialogBox&) = delete;

protected:
	const Window* const m_parent;
	HWND m_handle{ NULL };

	static INT_PTR SetupMessageHandling(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	virtual INT_PTR HandleMessage(UINT message, WPARAM wParam, LPARAM lParam) = 0;

private:
	static INT_PTR RouteMessage(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
};
