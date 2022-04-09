#pragma once
#include "WindowClass.h"
#include "EditorMenu.h"
#include "Graphics2D.h"

class EditorWindow final : public Window
{
public:
	Graphics2D graphics;

	EditorWindow(Vector2i size);

private:
	LRESULT HandleMessages(UINT message, WPARAM wParam, LPARAM lParam) override;

	void OnClose();
	void OnCommand(int controlIdentifier);

	void OnCreateButtonClick();
	void OnLoadButtonClick();
	void OnSaveButtonClick();

	void OnWallButtonClick();
	void OnRoadButtonClick();
	void OnCrossButtonClick();
	void OnBarrelButtonClick();
	void OnCharacterButtonClick();

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
