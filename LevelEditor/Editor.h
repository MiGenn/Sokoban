#pragma once
#include "Application.h"
#include "EditorWindow.h"

class Editor final : public Application
{
public:
	static const std::wstring ModulePath;

	Editor();
	Editor(const std::wstring& levelFileFullPath);
	Editor(const Editor&) = delete;

	Editor& operator=(const Editor&) = delete;

	int Run() override;

private:
	enum class EditorState : char
	{
		Editing,
		LevelSimulation
	};

	EditorWindow m_window;
	EditorState m_state{ EditorState::Editing };
	
	void Simulate();
	void Render();

	void RenderGrid();
	void RenderLevel();
};
