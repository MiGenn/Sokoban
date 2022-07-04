#include "Editor.h"

#include "WinapiUtilities.h"

const std::wstring Editor::modulePath{ Utilities::Winapi::GetModulePath(NULL) };

Editor::Editor() :
	m_window({ 1280, 720 }), m_simulator(m_window.keyboard, m_window.mouse, m_window.graphics)
{
	m_window.simulationStarted += [this]() { OnSimulationStarted(); };
	m_window.simulationEnded += [this]() { OnSimulationEnded(); };
}

Editor::Editor(const std::wstring& levelFileFullPath) : Editor()
{
	if (!levelFileFullPath.empty())
		if (!m_window.TryLoadLevel(levelFileFullPath))
			throw std::runtime_error("The file has an incorrect extension");
}

int Editor::Run()
{
	while (true)
	{
		WaitMessage();
		if (auto exitCode = RetrieveAndRouteMessages())
			return *exitCode;

		if (m_state == EditorState::Simulation)
			Simulate();
		Render();
	}
}

void Editor::Simulate()
{
	m_simulator.Simulate(*m_levelCopyForSimulation);
}

void Editor::Render()
{
	switch (m_state)
	{
	case Editor::EditorState::Editing:
		RenderGrid();
	case Editor::EditorState::Simulation:
		RenderLevel();
		break;
	}

	m_window.graphics.Present();
	m_window.graphics.Clear();
}

void Editor::RenderGrid()
{
	static constexpr int layerIndex{ 0 };
	static constexpr COLORREF lineColor{ RGB(128, 128, 128) };
	
	m_window.graphics.RenderGrid(layerIndex, lineColor);
}

void Editor::RenderLevel()
{
	if (auto level{ GetLevelForRendering() }; level)
		for (auto& entity : *level)
			m_window.graphics.RenderSprite(entity->GetRenderInfo());
}

const Level* Editor::GetLevelForRendering() const
{
	if (m_state == EditorState::Simulation)
		return m_levelCopyForSimulation.get();

	return m_window.GetLevel();
}

void Editor::OnSimulationStarted()
{
	m_state = EditorState::Simulation;
	m_levelCopyForSimulation = std::make_unique<Level>(*m_window.GetLevel());
}

void Editor::OnSimulationEnded()
{
	m_state = EditorState::Editing;
	m_levelCopyForSimulation.reset();
}
