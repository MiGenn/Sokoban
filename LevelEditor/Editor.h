#pragma once
#include "Application.h"
#include "EditorWindow.h"
#include "Simulator.h"

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

	EditorState m_state{ EditorState::Editing };
	EditorWindow m_window;
	Simulator m_simulator;
	std::unique_ptr<Level> m_levelCopy;
	
	void Simulate();
	void Render();

	void RenderGrid();
	void RenderLevel();

	void OnSimulationStartedOrEnded();
	const Level* GetLevelForRendering() const;
};
