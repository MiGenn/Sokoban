#include "EditorWindow.h"

#include <shlobj_core.h>
#include <commdlg.h>
#include "Editor.h"
#include "EnterTextBox.h"
#include "EditorResourceMacros.h"
#include "QuestionBox.h"
#include "SelectFolderBox.h"
#include "PathUtilities.h"
#include "FileUtilities.h"

#pragma comment(lib, "comdlg32")

#define CHECK MessageBox(NULL, L"Check", L"Check", MB_OK)

const EditorWindow::Class EditorWindow::Class::editorClass;

EditorWindow::EditorWindow(Vector2i size) : Window(size),
	graphics(this)
{
	const HINSTANCE moduleHandle{ GetModuleHandle(nullptr) };
	constexpr DWORD windowStyle{ WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_VISIBLE };

	RECT windowRect{ 0, 0, size.x, size.y };
	if (!AdjustWindowRect(&windowRect, windowStyle, true))
		throw WINAPI_LAST_EXCEPTION();

	m_handle = CreateWindow(Class::editorClass.GetName(), L"Level Editor", windowStyle, CW_USEDEFAULT, CW_USEDEFAULT,
		windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
		nullptr, LoadMenu(moduleHandle, MAKEINTRESOURCE(IDR_EDITOR_MENU)), moduleHandle, this);

	if (!m_handle)
		throw WINAPI_LAST_EXCEPTION();

	RegisterHotkeys();
}

LRESULT EditorWindow::HandleMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		OnClose();
		return 0;

	case WM_COMMAND:
		OnCommand(LOWORD(wParam));
		return 0;

	case WM_HOTKEY:
		OnHotkey((int)wParam);
		return 0;
	}

	return DefWindowProc(m_handle, message, wParam, lParam);
}

void EditorWindow::RegisterHotkeys()
{
	RegisterHotKey(m_handle, ID_EDITORWINDOW_CONTROL_S, MOD_CONTROL, 'S');
}

void EditorWindow::OnClose()
{
	PostQuitMessage(0);
	DestroyMenu(GetMenu(m_handle));
	DestroyWindow(m_handle);
}

void EditorWindow::OnCommand(int controlID)
{
	switch (controlID)
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

	case ID_GAMEOBJECTS_WALL:
		OnWallButtonClick();
		break;

	case ID_GAMEOBJECTS_ROAD:
		OnRoadButtonClick();
		break;

	case ID_GAMEOBJECTS_CROSS:
		OnCrossButtonClick();
		break;

	case ID_GAMEOBJECTS_BARREL:
		OnBarrelButtonClick();
		break;

	case ID_GAMEOBJECTS_CHARACTER:
		OnCharacterButtonClick();
		break;
	}
}
void EditorWindow::OnHotkey(int hotkeyID)
{
	switch (hotkeyID)
	{
	case ID_EDITORWINDOW_CONTROL_S:
		if (GetFocus() == m_handle)
			OnSaveButtonClick();
		break;
	}
}

void EditorWindow::OnCreateButtonClick()
{
	if (!m_level.IsNull() && m_level.IsChanged())
		SaveOrNotLevelBeforeLoadingOrCreatingNewOne();

	EnterTextBox enterTextBox(this);
	if (enterTextBox.GetText().empty())
	{
		MessageBox(m_handle, L"Level won't be created", L"Info", MB_ICONINFORMATION);
		return;
	}

	m_levelFullName = enterTextBox.GetText() + Level::FileExtension;
	m_level.ResetObject(new Level());

	if (!m_levelPath.empty())
	{
		QuestionBox questionBox(this, L"Use previous folder?");
		if (questionBox.IsCancelButtonPressed())
		{
			m_levelPath.clear();
			return;
		}

		if (!FileUtilities::DoesFileExist(m_levelPath))
		{
			MessageBox(m_handle, L"Previous path is invalid now. Choose new one", L"Error", MB_ICONERROR);
			SetOrNotLevelPathByUser();
		}
	}
}

void EditorWindow::OnLoadButtonClick()
{
	if (!m_level.IsNull() && m_level.IsChanged())
		SaveOrNotLevelBeforeLoadingOrCreatingNewOne();

	static wchar_t fileFullPathBuffer[MAX_PATH];
	fileFullPathBuffer[0] = L'\0';

	OPENFILENAME openFileName{};
	openFileName.lStructSize = sizeof(OPENFILENAME);
	openFileName.hwndOwner = m_handle;
	openFileName.lpstrFilter = L"Level files\0*.lvl\0";
	openFileName.lpstrFile = (LPWSTR)fileFullPathBuffer;
	openFileName.nMaxFile = MAX_PATH;
	openFileName.lpstrInitialDir = Editor::ModulePath.c_str();

	if (GetOpenFileName(&openFileName))
	{
		std::ifstream levelFile(openFileName.lpstrFile);
		m_level.ResetObject(new Level(levelFile));
		m_level.Reset();
		m_levelPath = PathUtilities::ExtractPath(openFileName.lpstrFile);
		m_levelFullName = PathUtilities::ExtractFullName(openFileName.lpstrFile);
	}
}

void EditorWindow::OnSaveButtonClick()
{
	//if (!m_level.IsChanged())
	//	return;

	if (m_level.IsNull())
	{
		MessageBox(m_handle, L"There is nothing to save", L"Error", MB_ICONERROR);
		return;
	}

	assert(m_levelFullName.empty() != true);

	if (m_levelPath.empty())
	{
		SetOrNotLevelPathByUser();
	}

	std::ofstream file(m_levelPath + m_levelFullName);
	if (!file.is_open())
	{
		MessageBox(m_handle, L"Cannot find level file folder. Choose new one", L"Error", MB_ICONERROR);
		m_levelPath.clear();
		OnSaveButtonClick();
		return;
	}

	m_level.Get().SerializeToOpenedFile(file);
	m_level.Reset();
}

void EditorWindow::OnWallButtonClick()
{
	
}

void EditorWindow::OnRoadButtonClick()
{
}

void EditorWindow::OnCrossButtonClick()
{
}

void EditorWindow::OnBarrelButtonClick()
{
}

void EditorWindow::OnCharacterButtonClick()
{
}

void EditorWindow::SetOrNotLevelPathByUser()
{
	SelectFolderBox selectFolderBox(this);
	if (!selectFolderBox.IsFolderSelected())
		return;

	m_levelPath = selectFolderBox.GetFolderFullPathWithTrailingBackslash();
}

void EditorWindow::SaveOrNotLevelBeforeLoadingOrCreatingNewOne()
{
	QuestionBox questionBox(this, L"Save current level?");
	if (questionBox.IsOKButtonPressed())
		OnSaveButtonClick();
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
