#include "EditorWindow.h"

#include "Editor.h"
#include "EnterTextBox.h"
#include "EditorResourceMacros.h"
#include "MenuHelper.h"
#include "QuestionBox.h"
#include "SelectFolderBox.h"
#include "StandardFileBox.h"
#include "FileUtilities.h"
#include "TiledEntityFactory.h"
#include "UnsafeUtilities.h"
#include "WinapiUtilities.h"

const EditorWindow::Class EditorWindow::Class::editorClass;
const std::wstring EditorWindow::m_editorName{ L"Level Editor" };
const std::wstring EditorWindow::m_levelHintText{ L"Enter level name" };

EditorWindow::EditorWindow(Vector2i size) : Window(size),
	graphics(this)
{
	const auto moduleHandle{ GetModuleHandle(nullptr) };
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

bool EditorWindow::TryLoadLevel(const std::wstring& fullPath)
{
	auto fullPathSize{ fullPath.size() };
	auto levelFileExtensionSize{ Level::fileExtension.size() };
	if (fullPathSize > levelFileExtensionSize)
	{
		auto fileExtension{ fullPath.substr(fullPathSize - levelFileExtensionSize, levelFileExtensionSize) };
		if (fileExtension == Level::fileExtension)
		{
			if (TryLoadLevelFromFile(fullPath))
			{
				OnLevelPathChanged();
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	
	MessageBox(m_handle, L"The program doesn't support the file extension", L"Error", MB_ICONERROR);
	return false;
}

const Level* EditorWindow::GetLevel() const noexcept
{
	return &m_level.Get();
}

bool EditorWindow::IsSimulation() const noexcept
{
	return m_isSimulation;
}

LRESULT EditorWindow::HandleMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (keyboard.m_isProcessed)
		keyboard.ResetState();

	if (mouse.m_isProcessed)
		mouse.ResetState();

	switch (message)
	{
	case WM_LBUTTONDOWN:
		OnLeftButtonClick(MAKEPOINTS(lParam));
		return 0;

	case WM_RBUTTONDOWN:
		OnRightButtonClick(MAKEPOINTS(lParam));
		return 0;

	case WM_MOUSEWHEEL:
		mouse.OnMouseScroll(GET_WHEEL_DELTA_WPARAM(wParam));
		OnMouseScroll();
		return 0;

	case WM_KEYDOWN:
		keyboard.OnKeyDown(static_cast<unsigned char>(wParam), (lParam & 0x40000000));
		MoveLevel();
		return 0;

	case WM_KEYUP:
		keyboard.OnKeyUp(static_cast<unsigned char>(wParam));
		return 0;

	case WM_KILLFOCUS:
		keyboard.ResetState();
		mouse.ResetState();
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
	if (!CanContinueBeforeDeletingOrResetingLevel())
		return;

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

	case ID_FILE_UNLOAD:
		OnUnloadButtonClick();
		break;

	case ID_FILE_SAVE:
		OnSaveButtonClick();
		break;

	case ID_FILE_SAVE_AS:
		OnSaveAsButtonClick();
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

	if (MenuHelper::IsOwned(controlID, ID_FILE))
		OnLevelPathChanged();
}
void EditorWindow::OnHotkey(HotKey hotKey)
{
	if (GetFocus() != m_handle)
		return;

	switch (hotKey)
	{
	case HotKey::ControlS:
		OnSaveButtonClick();
		break;
	}
}

void EditorWindow::OnLeftButtonClick(POINTS position)
{
	if (!CanDeleteOrAddEntity())
		return;

	SetCurrentEntityPosition(position);
	bool isAlreadyChanged{ m_level.IsChanged() };
	auto& level{ m_level.GetForEditing() };

	if (m_currentEntity->GetTag() == TiledEntity::Tag::Character && !level.IsPlaceOccupied(*m_currentEntity))
		if (auto character{ level.GetCharacter() }; character)
			character->SetPosition(m_currentEntity->GetPosition());

	if (!level.Add(std::make_unique<TiledEntity>(*m_currentEntity)))
		m_level.ResetState();

	if (isAlreadyChanged)
		m_level.GetForEditing();
}

void EditorWindow::OnRightButtonClick(POINTS position)
{
	if (!CanDeleteOrAddEntity())
		return;

	SetCurrentEntityPosition(position);
	bool isAlreadyChanged{ m_level.IsChanged() };
	auto& level{ m_level.GetForEditing() };
	auto equivalentEntity{ level.FindEquivalent(*m_currentEntity) };

	if (equivalentEntity != level.end())
		if (!level.Delete(equivalentEntity))
			m_level.ResetState();

	if (isAlreadyChanged)
		m_level.GetForEditing();
}

void EditorWindow::OnMouseScroll()
{
	if (IsSimulation())
		return;

	static constexpr auto zoomMin{ 0.05f };
	static constexpr auto zoomMax{ 20.f };

	auto zoom{ graphics.GetZoom() };
	auto scrollsCountAndDirection{ mouse.GetScrollsCountAndDirection() };

	while (scrollsCountAndDirection.first > 0)
	{
		zoom += zoom * m_scrollSensitivity * (int)scrollsCountAndDirection.second;
		--scrollsCountAndDirection.first;
	}

	zoom = std::clamp(zoom, zoomMin, zoomMax);
	graphics.SetZoom(zoom);
	mouse.m_isProcessed = false;
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
		auto newName{ enterTextBox.GetText() + Level::fileExtension };
		if (!m_levelPath.IsPathEmpty())
		{
			QuestionBox questionBox(this, L"Do you want to use the previous folder?");
			if (questionBox.IsOKButtonPressed())
			{
				if (!TryValidateLevelPathIfInvalid())
					return;

				if (TryValidateFullPathIfAnotherFileExists(m_levelPath.GetPath(), newName))
					newName = Utilities::Cpp::Unsafe::MakeNonConstForMove(m_levelPath.GetFullName());
				else
					return;
			}
			else
			{
				m_levelPath.ClearPath();
			}
		}

		m_levelPath.SetFullName(std::move(newName));
		m_level.ResetObject(new Level());
		OnLevelDeletedOrLoaded();
	}
}

void EditorWindow::OnLoadButtonClick()
{
	if (!CanContinueBeforeDeletingOrResetingLevel())
		return;

	StandardFileBox openFileBox(this, Editor::modulePath, m_levelFilter, StandardFileBox::Type::Open);
	if (openFileBox.IsOKButtonPressed())
		TryLoadLevelFromFile(openFileBox.GetFileFullPath());
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
		OnLevelDeletedOrLoaded();
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
		if (!m_level.IsChanged() || !IsLevelValid())
			return;

		if (m_levelPath.IsPathEmpty())
		{
			auto selectedPath = GetPathFromUser();
			if (!selectedPath.empty())
			{
				if (!TryValidateFullPathIfAnotherFileExists(selectedPath, m_levelPath.GetFullName()))
					return;
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
		if (!IsLevelValid())
			return;

		StandardFileBox saveFileBox(this, Editor::modulePath, m_levelFilter,
			StandardFileBox::Type::Save, StandardFileBox::Flag::OverwritePrompt, m_levelPath.GetFullName());
		if (saveFileBox.IsOKButtonPressed())
		{
			m_levelPath.SetFullPath(Utilities::Cpp::Unsafe::MakeNonConstForMove(saveFileBox.GetFileFullPath()));
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
		auto newName{ enterTextBox.GetText() + Level::fileExtension };
		if (!m_levelPath.GetFullPath().empty())
		{
			if (!m_levelPath.GetPath().empty() && !Utilities::Cpp::Path::IsPathValid(m_levelPath.GetPath()))
			{
				MessageBox(m_handle, L"Cannot find the folder", L"Error", MB_ICONERROR);
				m_levelPath.ClearPath();
			}
			else
			{
				TryValidateFullPathIfAnotherFileExists(m_levelPath.GetPath(), newName);
				m_level.GetForEditing();
				return;
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

void EditorWindow::OnPlayButtonClick()
{
	if (IsLevelValid())
	{
		m_isSimulation = true;
		ChangeSubmenusWhenSimulation(ChangeSubmenuOption::Disable);
		m_cameraPositionBeforeSimulation = graphics.GetCameraPosition();

		simulationStarted.Trigger();
	}
}

void EditorWindow::OnStopButtonClick()
{
	m_isSimulation = false;
	ChangeSubmenusWhenSimulation(ChangeSubmenuOption::Enable);
	graphics.SetCameraPosition(m_cameraPositionBeforeSimulation);

	simulationEnded.Trigger();
}

void EditorWindow::OnLevelDeletedOrLoaded()
{
	auto option{ ChangeSubmenuOption::Enable };
	if (m_level.IsNull())
		option = ChangeSubmenuOption::Disable;

	ChangeSubmenusWhenLevelIsDeletedOrLoaded(option);
}

void EditorWindow::OnLevelPathChanged()
{
	std::wstring additionalInfo;
	if (!m_levelPath.IsFullPathEmpty())
		additionalInfo = L" - " + m_levelPath.GetFullPath();
	
	SetWindowText(m_handle, (m_editorName + additionalInfo).c_str());;
}

void EditorWindow::ChangeSubmenusWhenLevelIsDeletedOrLoaded(ChangeSubmenuOption option)
{
	auto menuHandle{ GetMenu(m_handle) };

	EnableMenuItem(menuHandle, ID_GAMEOBJECTS, MF_BYPOSITION | (int)option);
	EnableMenuItem(menuHandle, ID_SIMULATION, MF_BYPOSITION | (int)option);

	InvalidateRect(Utilities::Winapi::FindMenuWindow(m_handle), NULL, true);
}

void EditorWindow::ChangeSubmenusWhenSimulation(ChangeSubmenuOption option)
{
	auto menuHandle{ GetMenu(m_handle) };

	EnableMenuItem(menuHandle, ID_FILE, MF_BYPOSITION | (int)option);
	EnableMenuItem(menuHandle, ID_GAMEOBJECTS, MF_BYPOSITION | (int)option);

	InvalidateRect(Utilities::Winapi::FindMenuWindow(m_handle), NULL, true);
}

void EditorWindow::SetCurrentEntityPosition(POINTS screenCoords)
{
	auto worldCoords{ graphics.ConvertScreenToWorldCoords({ screenCoords.x, screenCoords.y }) };
	Vector2f positionInGrid{ floor(worldCoords.x), ceil(worldCoords.y) };
	m_currentEntity->SetPosition(positionInGrid);
}

void EditorWindow::MoveLevel()
{
	if (IsSimulation())
		return;

	Vector2f translation;

	if (keyboard.IsKeyPressed('W'))
		translation += Vector2f(0.f, -1.f);

	if (keyboard.IsKeyPressed('S'))
		translation += Vector2f(0.f, 1.f);

	if (keyboard.IsKeyPressed('A'))
		translation += Vector2f(1.f, 0.f);

	if (keyboard.IsKeyPressed('D'))
		translation += Vector2f(-1.f, 0.f);

	graphics.SetCameraPosition(graphics.GetCameraPosition() + translation * m_drawingOriginMoveSensitivity);
	keyboard.m_isProcessed = false;
}

std::wstring EditorWindow::GetPathFromUser()
{
	SelectFolderBox selectFolderBox(this);
	return Utilities::Cpp::Unsafe::MakeNonConstForMove(selectFolderBox.GetFolderFullPathWithTrailingBackslash());
}

std::wstring EditorWindow::GetLevelFullNameFromUser()
{
	EnterTextBox enterTextBox(this, m_levelHintText);
	return enterTextBox.GetText() + Level::fileExtension;
}

bool EditorWindow::TrySaveLevelIntoFile()
{
	std::ofstream file(m_levelPath.GetFullPath(), std::ios::binary);
	if (file.is_open())
	{
		m_level.Get().SerializeToOpenedFile(file);
		m_level.ResetState();
		return true;
	}

	return false;
}

bool EditorWindow::TryLoadLevelFromFile(const std::wstring& fullPath)
{
	std::ifstream levelFile(fullPath, std::ios::binary);
	if (levelFile.is_open())
	{
		try
		{
			m_level.ResetObject(new Level(levelFile));
			m_level.ResetState();
			m_levelPath.SetFullPath(fullPath);
			OnLevelDeletedOrLoaded();
			return true;
		}
		catch (...)
		{
			MessageBox(m_handle, L"The level file is corrupted", L"Error", MB_ICONERROR);
		}
	}
	else
	{
		MessageBox(m_handle, L"Cannot open the file", L"Error", MB_ICONERROR);
	}
	
	return false;
}

bool EditorWindow::TryValidateLevelPathIfInvalid()
{
	if (!Utilities::Cpp::Path::IsPathValid(m_levelPath.GetPath()))
	{
		MessageBox(m_handle, L"The folder is invalid. Choose a new one", L"Error", MB_ICONERROR);
		m_levelPath.SetPath(GetPathFromUser());
		if (m_levelPath.IsPathEmpty())
			return false;
	}

	return true;
}

bool EditorWindow::TryValidateFullPathIfAnotherFileExists(const std::wstring& validNewPath, const std::wstring& newFullName)
{
	auto fullPath{ validNewPath + newFullName };
	if (Utilities::Cpp::Path::IsPathValid(fullPath))
	{
		QuestionBox questionBox(this, newFullName + L" already exists in the folder. Do you want to replace it?");
		if (questionBox.IsCancelButtonPressed())
		{
			StandardFileBox saveFileBox(this, validNewPath, m_levelFilter,
				StandardFileBox::Type::Save, StandardFileBox::Flag::OverwritePrompt, newFullName);
			if (saveFileBox.IsOKButtonPressed())
			{
				m_levelPath.SetFullPath(Utilities::Cpp::Unsafe::MakeNonConstForMove(saveFileBox.GetFileFullPath()));
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	m_levelPath.SetFullPath(std::move(fullPath));
	return true;
}

bool EditorWindow::CanContinueBeforeDeletingOrResetingLevel()
{
	if (!m_level.IsNull() && m_level.IsChanged())
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

bool EditorWindow::CanDeleteOrAddEntity()
{
	return !m_level.IsNull() && m_currentEntity;
}

bool EditorWindow::IsLevelValid()
{
	bool isValid{ true };
	auto& level{ m_level.GetForEditing() };
	if (!level.GetCharacter())
	{
		MessageBox(m_handle, L"The level must contain the character", L"Error", MB_ICONERROR);
		isValid = false;
	}

	if (level.GetBarrels().size() != level.GetCrosses().size())
	{
		MessageBox(m_handle, L"The level must contain the same number of barrels and crosses", L"Error", MB_ICONERROR);
		isValid = false;
	}

	return isValid;
}

EditorWindow::Class::Class() : WindowClass(L"SokobanEditor")
{
	WNDCLASSEX wcex{ sizeof(wcex) };
	wcex.lpszClassName = GetName();
	wcex.hInstance = GetModuleHandle(NULL);
	wcex.lpfnWndProc = SetupMessageHandling;
	wcex.hIcon = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON));
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON));

	if (!RegisterClassEx(&wcex))
		throw WINAPI_LAST_EXCEPTION();
}
