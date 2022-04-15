#pragma once
#include "WindowClass.h"
#include "Graphics2D.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Level.h"
#include "ChangeWrapper.h"
#include "Path.h"

class EditorWindow final : public Window
{
public:
	Mouse mouse;
	Keyboard keyboard;
	Graphics2D graphics;

	EditorWindow(Vector2i size);

private:
	enum class HotKey
	{
		ControlS,
	};

	static const std::wstring m_editorName;
	static constexpr const wchar_t* m_levelFilter{ L"Level Files\0*.lvl\0" };
	static const std::wstring m_levelHintText;

	ChangeWrapper<Level> m_level{ nullptr };
	Path m_levelPath;

	std::unique_ptr<TiledEntity> m_currentEntity;

	LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam) override;
	void RegisterHotKeys();

	void OnClose();
	void OnCommand(int controlID);
	void OnHotkey(HotKey hotKey);

	void OnCreateButtonClick();
	void OnLoadButtonClick();
	void OnUnloadButtonClick();
	void OnSaveButtonClick();
	void OnSaveAsButtonClick();
	void OnRenameButtonClick();

	void OnWallButtonClick();
	void OnRoadButtonClick();
	void OnCrossButtonClick();
	void OnBarrelButtonClick();
	void OnCharacterButtonClick();

	void OnPlayButtonClick();
	void OnStopButtonClick();

	void OnLevelPathChanged();
	void ChangeMenuItemsWhenSimulation(int option);

	std::pair<std::wstring, std::wstring> GetLevelSplittedFullPathFromUser();
	std::wstring GetPathFromUser();
	std::wstring GetLevelFullNameFromUser();

	bool TrySaveLevelIntoFile();
	bool AlreadyExists(const std::wstring& levelFullName);
	bool CanContinueBeforeDeletingOrResetingLevel();
	bool CanLevelBeSaved();

	class Class : public WindowClass
	{
	public:
		static const Class editorClass;

	private:
		Class();
		Class(const Class&) = delete;
		Class& operator=(const Class&) = delete;
	};
};
