#pragma once
#include "Application.h"
#include "EditorWindow.h"
#include "Simulator.h"

class Editor final : public Application
{
public:
	static const std::wstring modulePath;

	Editor() noexcept;
	Editor(const std::wstring& levelFileFullPath);
	Editor(const Editor&) = delete;
	
	Editor& operator=(const Editor&) = delete;

	int Run() override;

private:
	enum class EditorState : char
	{
		Editing,
		Simulation
	};

	EditorState m_state{ EditorState::Editing };
	EditorWindow m_window;
	Simulator m_simulator;
	std::unique_ptr<Level> m_levelCopyForSimulation;
	
	void Simulate() NOEXCEPT_WHEN_NDEBUG;
	void Render();

	void RenderGrid() noexcept;
	void RenderLevel() noexcept;

	const Level* GetLevelForRendering() const noexcept;

	void OnSimulationStarted() noexcept;
	void OnSimulationEnded() noexcept;
};
