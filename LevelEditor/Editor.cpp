#include "Editor.h"

#include "WinapiUntilities.h"

#define CHECK MessageBox(NULL, L"Check", L"Check", MB_OK)

const std::wstring Editor::ModulePath{ WinapiUntilities::GetModulePath(NULL) };

Editor::Editor() :
	m_window({ 1280, 720 })
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
		if (auto exitCode = RetrieveAndRouteMessages())
			return *exitCode;

		if (m_window.IsSimulation())
			m_state = EditorState::LevelSimulation;
		else
			m_state = EditorState::Editing;

		Simulate();
		Render();

		WaitMessage();
	}
}

void Editor::Simulate()
{
	switch (m_state)
	{
	case Editor::EditorState::LevelSimulation:
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
	auto* level{ m_window.GetLevel() };
	if (level == nullptr)
		return;

	for (auto& entity : *level)
		m_window.graphics.RenderSprite(entity->GetRenderInfo());
}
