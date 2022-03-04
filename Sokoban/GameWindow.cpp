#include "GameWindow.h"

GameWindow::GameWindow(int width, int height) : 
	Window(width, height), graphics(this)
{
	constexpr DWORD windowStyle{ WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_VISIBLE };

	RECT windowRect{ 0, 0, width, height };
	if (!AdjustWindowRect(&windowRect, windowStyle, false))
		throw LAST_EXCEPTION();

	m_handle = CreateWindow(Class::gameWindow.GetName(), L"Sokoban", windowStyle, CW_USEDEFAULT, CW_USEDEFAULT,
		windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, 
		nullptr, nullptr, GetModuleHandle(nullptr), this);

	if (!m_handle)
		throw LAST_EXCEPTION();
}

LRESULT GameWindow::HandleMessages(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		mouse.OnLeftButtonPressed();
		return 0;

	case WM_MOUSEMOVE:
		mouse.OnMouseMove(MAKEPOINTS(lParam));
		return 0;

	case WM_KEYDOWN:
		keyboard.OnKeyDown(static_cast<unsigned char>(wParam), (lParam & 0x40000000));
		return 0;

	case WM_KEYUP:
		keyboard.OnKeyUp(static_cast<unsigned char>(wParam));
		return 0;

	case WM_KILLFOCUS:
		keyboard.ResetState();
		return 0;

	case WM_CLOSE:
		OnClose();
		return 0;
	}

	return DefWindowProc(m_handle, message, wParam, lParam);
}

void GameWindow::OnClose()
{
	PostQuitMessage(0);
	DestroyWindow(m_handle);
}

const GameWindow::Class GameWindow::Class::gameWindow;

GameWindow::Class::Class() : WindowClass(L"SokobanGame")
{
	WNDCLASSEX wcex{ sizeof(wcex) };
	wcex.lpszClassName = GetName();
	wcex.hInstance = GetModuleHandle(nullptr);
	wcex.lpfnWndProc = SetupMessageHandling;

	if (!RegisterClassEx(&wcex))
		throw LAST_EXCEPTION();
}
