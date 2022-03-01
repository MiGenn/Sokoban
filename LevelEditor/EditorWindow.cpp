#include "EditorWindow.h"

const EditorWindow::Class EditorWindow::Class::editorClass;

EditorWindow::EditorWindow(int width, int height) : Window(width, height)
{
	constexpr DWORD windowStyle{ WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_VISIBLE };

	RECT windowRect{ 0, 0, width, height };
	if (!AdjustWindowRect(&windowRect, windowStyle, false))
		throw LAST_EXCEPTION();

	m_handle = CreateWindow(Class::editorClass.GetName(), L"Level Editor", windowStyle, CW_USEDEFAULT, CW_USEDEFAULT,
		windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
		nullptr, nullptr, GetModuleHandle(nullptr), this);

	if (!m_handle)
		throw LAST_EXCEPTION();
}

LRESULT EditorWindow::HandleMessages(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(m_handle, message, wParam, lParam);
}

EditorWindow::Class::Class() : WindowClass(L"SokobanEditor")
{
	WNDCLASSEX wcex{ sizeof(wcex) };
	wcex.lpszClassName = GetName();
	wcex.hInstance = GetModuleHandle(nullptr);
	wcex.lpfnWndProc = SetupMessageHandling;

	if (!RegisterClassEx(&wcex))
		throw LAST_EXCEPTION();
}
