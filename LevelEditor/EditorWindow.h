#pragma once
#include "WindowClass.h"
#include "Graphics2D.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Level.h"
#include "ChangeWrapper.h"

class EditorWindow final : public Window
{
public:
	Mouse mouse;
	Keyboard keyboard;
	Graphics2D graphics;

	EditorWindow(Vector2i size);

private:
	ChangeWrapper<Level> m_level{ nullptr };
	std::wstring m_levelPath;
	std::wstring m_levelFullName;

	LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam) override;
	void RegisterHotkeys();

	void OnClose();
	void OnCommand(int controlID);
	void OnHotkey(int hotkeyID);

	void OnCreateButtonClick();
	void OnLoadButtonClick();
	void OnSaveButtonClick();

	void OnWallButtonClick();
	void OnRoadButtonClick();
	void OnCrossButtonClick();
	void OnBarrelButtonClick();
	void OnCharacterButtonClick();

	void SetOrNotLevelPathByUser();
	void SaveOrNotLevelBeforeLoadingOrCreatingNewOne();

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
