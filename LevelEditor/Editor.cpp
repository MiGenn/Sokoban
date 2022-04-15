#include "Editor.h"

#include "WinapiUntilities.h"

const std::wstring Editor::ModulePath{ WinapiUntilities::GetModulePath(NULL) };

Editor::Editor() :
	m_window({ 1280, 720 })
{

}

int Editor::Run()
{
	while (true)
	{
		if (auto exitCode = RetrieveAndRouteMessages())
			return *exitCode;

		Simulate();
		Render();

		WaitMessage();
	}
}

void Editor::Simulate()
{
	switch (m_state)
	{
	case Editor::EditorState::Editing:
		break;

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
		break;

	case Editor::EditorState::LevelSimulation:
		break;
	}

	m_window.graphics.Present();
}

void Editor::RenderGrid()
{
	static constexpr int layerIndex{ 0 };
	static Vector2i startPosition(0, 0);
	static Vector2i endPosition(m_window.GetSize());
	static Vector2i sellSize(TiledEntity::tileSize, TiledEntity::tileSize);
	static constexpr COLORREF lineColor{ RGB(128, 128, 128) };
	
	m_window.graphics.RenderGrid(layerIndex, startPosition, endPosition, sellSize, lineColor);
}
