#include "Game.h"

Game::Game() :
	m_window(1280, 720)
{

}

int Game::Run()
{
	//LoadScene();

	while (true)
	{
		if (auto exitCode = RetrieveAndRouteMessages())
			return *exitCode;

		Simulate();
		Render();

		WaitMessage();
	}
}

void Game::Simulate()
{
	//[currentSceneName]

	if (m_window.keyboard.IsKeyPressed('Q'))
		m_window.graphics.Test();
}

void Game::Render()
{
	/*for (auto& entity : scenes[currentSceneName]->entities)
	{
		auto renderInfo = static_cast<SpriteRenderInfo*>(entity.components[Entity2D::renderInfoIndex]);
		if (renderInfo != nullptr && renderInfo.IsEnabled())
			m_window.graphics.RenderSprite(renderInfo);	
	}*/

	m_window.graphics.Present();
}
