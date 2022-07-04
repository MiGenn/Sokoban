#include "GameWindow.h"

#include "GameResourceMacros.h"
#include "Game.h"
#include "StandardFileBox.h"

GameWindow::GameWindow(Vector2i size) :
	Window(size), graphics(this)
{
	const auto moduleHandle{ GetModuleHandle(nullptr) };
	constexpr DWORD windowStyle{ WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_VISIBLE };

	RECT windowRect{ 0, 0, size.x, size.y };
	if (!AdjustWindowRect(&windowRect, windowStyle, false))
		throw WINAPI_LAST_EXCEPTION();

	m_handle = CreateWindow(Class::gameWindow.GetName(), L"Sokoban", windowStyle, CW_USEDEFAULT, CW_USEDEFAULT,
		windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, 
		nullptr, LoadMenu(moduleHandle, MAKEINTRESOURCE(IDR_GAME_MENU)), moduleHandle, this);

	if (!m_handle)
		throw WINAPI_LAST_EXCEPTION();

	RegisterHotKey(m_handle, (int)HotKey::Restart, NULL, 'R');
}

void GameWindow::Resize(Vector2i size)
{
	Window::Resize(size);
	graphics.ResizeLayers(size);
}

LRESULT GameWindow::HandleMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (keyboard.m_isProcessed)
		keyboard.ResetState();

	if (mouse.m_isProcessed)
		mouse.ResetState();

	switch (message)
	{
	case WM_MOUSEWHEEL:
		mouse.OnMouseScroll(GET_WHEEL_DELTA_WPARAM(wParam));
		return 0;

	case WM_KEYDOWN:
		keyboard.OnKeyDown(static_cast<unsigned char>(wParam), (lParam & 0x40000000));
		return 0;

	case WM_KEYUP:
		keyboard.OnKeyUp(static_cast<unsigned char>(wParam));
		return 0;

	case WM_KILLFOCUS:
		keyboard.ResetState();
		mouse.ResetState();
		return 0;

	case WM_COMMAND:
		OnCommand((int)wParam);
		return 0;

	case WM_HOTKEY:
		OnHotKey((HotKey)wParam);
		break;

	case WM_CLOSE:
		OnClose();
		return 0;
	}

	return DefWindowProc(m_handle, message, wParam, lParam);
}

void GameWindow::OnClose() noexcept
{
	PostQuitMessage(0);
	DestroyWindow(m_handle);
}

void GameWindow::OnCommand(int controlID)
{
	switch (controlID)
	{
	case ID_RESTART:
		OnRestartButtonClick();
		break;

	case ID_LOAD_LEVEL:
		OnLoadLevelButtonClick();
		break;
	}
}

void GameWindow::OnRestartButtonClick()
{
	reloadButtonIsClicked.Trigger();
}

void GameWindow::OnLoadLevelButtonClick()
{
	StandardFileBox openFileBox(this, Game::modulePath, m_levelFilter, StandardFileBox::Type::Open);
	if (openFileBox.IsOKButtonPressed())
		loadLevelButtonIsClicked.Trigger(openFileBox.GetFileFullPath());
}

void GameWindow::OnHotKey(HotKey hotKey)
{
	switch (hotKey)
	{
	case HotKey::Restart:
		OnRestartButtonClick();
		break;
	}
}

const GameWindow::Class GameWindow::Class::gameWindow;

GameWindow::Class::Class() : WindowClass(L"SokobanGame")
{
	WNDCLASSEX wcex{ sizeof(wcex) };
	wcex.lpszClassName = GetName();
	wcex.hInstance = GetModuleHandle(nullptr);
	wcex.lpfnWndProc = SetupMessageHandling;
	wcex.hIcon = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON));
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON));

	if (!RegisterClassEx(&wcex))
		throw WINAPI_LAST_EXCEPTION();
}
