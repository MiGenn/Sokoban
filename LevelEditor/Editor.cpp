#include "Editor.h"

#include "WinapiUntilities.h"

const std::wstring Editor::ModulePath{ WinapiUntilities::GetModulePath(NULL) };

Editor::Editor() :
	m_window({ 1280, 720 }), m_simulator(m_window.keyboard, m_window.mouse)
{

}

Editor::Editor(const std::wstring& levelFileFullPath) : Editor()
{
	if (!levelFileFullPath.empty())
	{
		if (!m_window.TryLoadLevel(levelFileFullPath))
			throw std::runtime_error("The program won't start");
	}
}

int Editor::Run()
{
	while (true)
	{
		WaitMessage();
		if (auto exitCode = RetrieveAndRouteMessages())
			return *exitCode;

		OnSimulationStartedOrEnded();
		Simulate();
		Render();
	}
}

void Editor::Simulate()
{
	switch (m_state)
	{
	case Editor::EditorState::LevelSimulation:
		m_simulator.Simulate(*m_levelCopy);
		break;
	}
}

void Editor::Render()
{
	switch (m_state)
	{
	case Editor::EditorState::Editing:
		RenderGrid();
	case Editor::EditorState::LevelSimulation:
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
	if (auto level{ GetLevelForRendering() }; level != nullptr)
	{
		for (auto& entity : *level)
			m_window.graphics.RenderSprite(entity->GetRenderInfo());
	}
}

void Editor::OnSimulationStartedOrEnded()
{
	if (m_window.IsSimulation())
	{
		m_state = EditorState::LevelSimulation;
		if (!m_levelCopy)
			m_levelCopy = std::make_unique<Level>(*m_window.GetLevel());
	}
	else
	{
		m_state = EditorState::Editing;
		if (m_levelCopy)
			m_levelCopy.reset();
	}
}

const Level* Editor::GetLevelForRendering() const
{
	if (m_state == EditorState::LevelSimulation)
		return m_levelCopy.get();

	return m_window.GetLevel();
}
