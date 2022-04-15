#include "EditorWindow.h"

#include "Editor.h"
#include "EnterTextBox.h"
#include "EditorResourceMacros.h"
#include "QuestionBox.h"
#include "SelectFolderBox.h"
#include "StandardFileBox.h"
#include "FileUtilities.h"
#include "TiledEntityFactory.h"
#include "UnsafeUtilities.h"
#include "WinapiUntilities.h"

#define CHECK MessageBox(NULL, L"Check", L"Check", MB_OK)

const EditorWindow::Class EditorWindow::Class::editorClass;
const std::wstring EditorWindow::m_editorName{ L"Level Editor" };
const std::wstring EditorWindow::m_levelHintText{ L"Enter level name" };

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

	RegisterHotKeys();
}

LRESULT EditorWindow::HandleMessage(UINT message, WPARAM wParam, LPARAM lParam)
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

	case WM_COMMAND:
		OnCommand(LOWORD(wParam));
		return 0;

	case WM_HOTKEY:
		OnHotkey((HotKey)wParam);
		return 0;

	case WM_CLOSE:
		OnClose();
		return 0;
	}

	return DefWindowProc(m_handle, message, wParam, lParam);
}

void EditorWindow::RegisterHotKeys()
{
	RegisterHotKey(m_handle, (int)HotKey::ControlS, MOD_CONTROL, 'S');
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
		OnLevelPathChanged();
		break;

	case ID_FILE_LOAD:
		OnLoadButtonClick();
		OnLevelPathChanged();
		break;

	case ID_FILE_UNLOAD:
		OnUnloadButtonClick();
		OnLevelPathChanged();
		break;

	case ID_FILE_SAVE:
		OnSaveButtonClick();
		OnLevelPathChanged();
		break;

	case ID_FILE_SAVE_AS:
		OnSaveAsButtonClick();
		OnLevelPathChanged();
		break;

	case ID_FILE_RENAME:
		OnRenameButtonClick();
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

	case ID_SIMULATION_PLAY:
		OnPlayButtonClick();
		break;

	case ID_SIMULATION_STOP:
		OnStopButtonClick();
		break;
	}
}
void EditorWindow::OnHotkey(HotKey hotKey)
{
	switch (hotKey)
	{
	case HotKey::ControlS:
		if (GetFocus() == m_handle)
			OnSaveButtonClick();
		break;
	}
}

void EditorWindow::OnCreateButtonClick()
{
	if (!CanContinueBeforeDeletingOrResetingLevel())
		return;

	EnterTextBox enterTextBox(this, m_levelHintText);
	if (enterTextBox.IsOKButtonPressed() && enterTextBox.GetText().empty())
	{
		MessageBox(m_handle, L"The entered name is empty.\nThe Level won't be created", L"Error", MB_ICONERROR);
	}
	else if (enterTextBox.IsOKButtonPressed())
	{
		auto newName{ enterTextBox.GetText() + Level::FileExtension };
		if (!m_levelPath.IsPathEmpty())
		{
			QuestionBox questionBox(this, L"Do you want to use the previous folder?");
			if (questionBox.IsOKButtonPressed())
			{
				if (!FileUtilities::IsPathValid(m_levelPath.GetPath()))
				{
					MessageBox(m_handle, L"The previous path is invalid. Choose a new one", L"Error", MB_ICONERROR);
					m_levelPath = GetPathFromUser();
					if (m_levelPath.IsPathEmpty())
						return;
				}
				//
				if (FileUtilities::IsPathValid(m_levelPath.GetPath() + newName))
				{
					QuestionBox questionBox(this, newName + L" already exists in the folder. Do you want to replace it?");
					if (questionBox.IsCancelButtonPressed())
					{
						StandardFileBox saveFileBox(this, m_levelPath.GetPath(), m_levelFilter,
							StandardFileBox::Type::Save, OFN_OVERWRITEPROMPT, newName);
						if (saveFileBox.IsOKButtonPressed())
						{
							m_levelPath.SetFullPath(UnsafeUtilities::MakeNonConstForMove(saveFileBox.GetFileFullPath()));
							m_level.ResetObject(new Level());
							return;
						}
						else
						{
							return;
						}
					}
				}
				//
			}
			else
			{
				m_levelPath.ClearPath();
			}
		}

		m_levelPath.SetFullName(std::move(newName));
		m_level.ResetObject(new Level());
	}
}

void EditorWindow::OnLoadButtonClick()
{
	if (!CanContinueBeforeDeletingOrResetingLevel())
		return;

	StandardFileBox openFileBox(this, Editor::ModulePath, 
		m_levelFilter, StandardFileBox::Type::Open);
	if (openFileBox.IsOKButtonPressed())
	{
		std::ifstream levelFile(openFileBox.GetFileFullPath());
		m_level.ResetObject(new Level(levelFile));
		m_level.ResetState();

		m_levelPath.SetFullPath(UnsafeUtilities::MakeNonConstForMove(openFileBox.GetFileFullPath()));
	}
}

void EditorWindow::OnUnloadButtonClick()
{
	if (m_level.IsNull())
	{
		MessageBox(m_handle, L"There is nothing to unload", L"Error", MB_ICONEXCLAMATION);
	}
	else
	{
		if (!CanContinueBeforeDeletingOrResetingLevel())
			return;

		m_level.ResetObject(nullptr);
		m_levelPath.ClearFullPath();
	}
}

void EditorWindow::OnSaveButtonClick()
{
	if (m_level.IsNull())
	{
		MessageBox(m_handle, L"There is nothing to save", L"Error", MB_ICONEXCLAMATION);
	}
	else
	{
		assert(m_levelPath.IsFullNameEmpty() != true);
		if (!m_level.IsChanged())
			return;

		if (m_levelPath.IsPathEmpty())
		{
			auto selectedPath = GetPathFromUser();
			if (!selectedPath.empty())
			{
				if (FileUtilities::IsPathValid(selectedPath + m_levelPath.GetFullName()))
				{
					QuestionBox questionBox(this, m_levelPath.GetFullName() + L" already exists in the folder. Do you want to replace it?");
					if (questionBox.IsCancelButtonPressed())
					{
						StandardFileBox saveFileBox(this, Editor::ModulePath, m_levelFilter,
							StandardFileBox::Type::Save, OFN_OVERWRITEPROMPT, m_levelPath.GetFullName());
						if (saveFileBox.IsOKButtonPressed())
						{
							m_levelPath.SetFullPath(UnsafeUtilities::MakeNonConstForMove(saveFileBox.GetFileFullPath()));
						}
						else
						{
							return;
						}
					}
				}

				if (m_levelPath.IsPathEmpty())
					m_levelPath.SetPath(std::move(selectedPath));
			}
			else
			{
				return;
			}
		}

		if (!TrySaveLevelIntoFile())
		{
			MessageBox(m_handle, L"Cannot find the file folder.\nChoose a new one", L"Error", MB_ICONERROR);
			m_levelPath.ClearPath();
			OnSaveButtonClick();
		}
	}
}

void EditorWindow::OnSaveAsButtonClick()
{
	if (m_level.IsNull())
	{
		MessageBox(m_handle, L"There is nothing to save", L"Error", MB_ICONEXCLAMATION);
	}
	else
	{
		StandardFileBox saveFileBox(this, Editor::ModulePath, m_levelFilter,
			StandardFileBox::Type::Save, OFN_OVERWRITEPROMPT, m_levelPath.GetFullName());
		if (saveFileBox.IsOKButtonPressed())
		{
			m_levelPath.SetFullPath(UnsafeUtilities::MakeNonConstForMove(saveFileBox.GetFileFullPath()));
			TrySaveLevelIntoFile();
		}
	}
}

void EditorWindow::OnRenameButtonClick()
{
	if (m_level.IsNull())
	{
		MessageBox(m_handle, L"There is nothing to rename", L"Error", MB_ICONERROR);
		return;
	}

	EnterTextBox enterTextBox(this, m_levelHintText);
	if (enterTextBox.IsOKButtonPressed() && enterTextBox.GetText().empty())
	{
		MessageBox(m_handle, L"The entered name is empty.\nThe Level won't be renamed", L"Error", MB_ICONERROR);
	}
	else if (enterTextBox.IsOKButtonPressed())
	{
		auto newName{ enterTextBox.GetText() + Level::FileExtension };
		if (!m_levelPath.GetFullPath().empty())
		{
			if (!FileUtilities::IsPathValid(m_levelPath.GetFullPath()))
			{
				MessageBox(m_handle, L"Cannot find the folder", L"Error", MB_ICONERROR);
				m_levelPath.ClearPath();
			}

			if (FileUtilities::IsPathValid(m_levelPath.GetPath() + newName))
			{
				QuestionBox questionBox(this, newName + L" already exists in the folder. Do you want to replace it?");
				if (questionBox.IsCancelButtonPressed())
				{
					StandardFileBox saveFileBox(this, m_levelPath.GetPath(), m_levelFilter,
						StandardFileBox::Type::Save, OFN_OVERWRITEPROMPT, newName);
					if (saveFileBox.IsOKButtonPressed())
					{
						m_levelPath.SetFullPath(UnsafeUtilities::MakeNonConstForMove(saveFileBox.GetFileFullPath()));
					}

					return;
				}
				else
				{
					m_levelPath.SetFullName(std::move(newName));
					m_level.GetForEditing();
					OnSaveButtonClick();
					return;
				}
			}
		}

		m_levelPath.SetFullName(std::move(newName));
		m_level.GetForEditing();
	}
}

void EditorWindow::OnWallButtonClick()
{
	m_currentEntity = TiledEntityFactory::CreateWall();
}

void EditorWindow::OnRoadButtonClick()
{
	m_currentEntity = TiledEntityFactory::CreateRoad();
}

void EditorWindow::OnCrossButtonClick()
{
	m_currentEntity = TiledEntityFactory::CreateCross();
}

void EditorWindow::OnBarrelButtonClick()
{
	m_currentEntity = TiledEntityFactory::CreateBarrel();
}

void EditorWindow::OnCharacterButtonClick()
{
	m_currentEntity = TiledEntityFactory::CreateCharacter();
}

void EditorWindow::OnLevelPathChanged()
{
	std::wstring additionalInfo;
	if (!m_levelPath.IsFullPathEmpty())
		additionalInfo = L" - " + m_levelPath.GetFullPath();
	
	SetWindowText(m_handle, (m_editorName + additionalInfo).c_str());;
}

void EditorWindow::ChangeMenuItemsWhenSimulation(int option)
{
	auto menuHandle{ GetMenu(m_handle) };

	EnableMenuItem(menuHandle, ID_FILE, MF_BYPOSITION | option);
	EnableMenuItem(menuHandle, ID_GAMEOBJECTS, MF_BYPOSITION | option);

	InvalidateRect(WinapiUntilities::FindMenu(m_handle), NULL, true);
}

void EditorWindow::OnPlayButtonClick()
{
	ChangeMenuItemsWhenSimulation(MF_GRAYED);
}

void EditorWindow::OnStopButtonClick()
{
	ChangeMenuItemsWhenSimulation(MF_ENABLED);
}

std::wstring EditorWindow::GetPathFromUser()
{
	SelectFolderBox selectFolderBox(this);
	return UnsafeUtilities::MakeNonConstForMove(selectFolderBox.GetFolderFullPathWithTrailingBackslash());
}

std::wstring EditorWindow::GetLevelFullNameFromUser()
{
	EnterTextBox enterTextBox(this, m_levelHintText);
	return enterTextBox.GetText() + Level::FileExtension;
}

bool EditorWindow::TrySaveLevelIntoFile()
{
	std::ofstream file(m_levelPath.GetFullPath());
	if (file.is_open())
	{
		m_level.Get().SerializeToOpenedFile(file);
		m_level.ResetState();
		return true;
	}

	return false;
}

bool EditorWindow::AlreadyExists(const std::wstring& levelFullName)
{ ///////
	return false;
}

bool EditorWindow::CanContinueBeforeDeletingOrResetingLevel()
{
	if (CanLevelBeSaved())
	{
		QuestionBox questionBox(this, L"Do you want to save the current level?");
		if (questionBox.IsOKButtonPressed())
		{
			OnSaveButtonClick();
			return !m_level.IsChanged();
		}
	}

	return true;
}

bool EditorWindow::CanLevelBeSaved()
{
	return !m_level.IsNull() && m_level.IsChanged();
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
