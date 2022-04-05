#include "EditorWindow.h"

const EditorWindow::Class EditorWindow::Class::editorClass;

EditorWindow::EditorWindow(int width, int height) : Window(width, height),
	graphics(this)
{
	const HINSTANCE moduleHandle{ GetModuleHandle(nullptr) };
	constexpr DWORD windowStyle{ WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_VISIBLE };

	RECT windowRect{ 0, 0, width, height };
	if (!AdjustWindowRect(&windowRect, windowStyle, true))
		throw WINAPI_LAST_EXCEPTION();

	m_handle = CreateWindow(Class::editorClass.GetName(), L"Level Editor", windowStyle, CW_USEDEFAULT, CW_USEDEFAULT,
		windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
		nullptr, LoadMenu(moduleHandle, MAKEINTRESOURCE(IDR_EDITOR_MENU)), moduleHandle, this);

	if (!m_handle)
		throw WINAPI_LAST_EXCEPTION();
}

LRESULT EditorWindow::HandleMessages(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		OnClose();
		return 0;

	case WM_COMMAND:
		OnCommand(LOWORD(wParam));
		return 0;
	}

	return DefWindowProc(m_handle, message, wParam, lParam);
}

void EditorWindow::OnClose()
{
	PostQuitMessage(0);
	DestroyMenu(GetMenu(m_handle));
	DestroyWindow(m_handle);
}

void EditorWindow::OnCommand(int controlIdentifier)
{
	switch (controlIdentifier)
	{
	case ID_FILE_CREATE:
		OnCreateButtonClick();
		break;

	case ID_FILE_LOAD:
		OnLoadButtonClick();
		break;

	case ID_FILE_SAVE:
		OnSaveButtonClick();
		break;
	}
}

void EditorWindow::OnCreateButtonClick()
{

}

void EditorWindow::OnLoadButtonClick()
{

}

void EditorWindow::OnSaveButtonClick()
{

}

EditorWindow::Class::Class() : WindowClass(L"SokobanEditor")
{
	WNDCLASSEX wcex{ sizeof(wcex) };
	wcex.lpszClassName = GetName();
	wcex.hInstance = GetModuleHandle(nullptr);
	wcex.lpfnWndProc = SetupMessageHandling;

	if (!RegisterClassEx(&wcex))
		throw WINAPI_LAST_EXCEPTION();
}
