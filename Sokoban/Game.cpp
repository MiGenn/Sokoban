#include "Game.h"

Game::Game() :
	m_window(1280, 720)
{

}

Game::~Game()
{
	delete m_currentLevel;
}

int Game::Run()
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

void Game::Simulate()
{
	switch (m_state)
	{
	case Game::GameState::MainMenu:
		SimulateMainMenu();
		break;

	case Game::GameState::EscMenu:
		break;

	case Game::GameState::Level:
		break;
	}
}

void Game::Render()
{
	switch (m_state)
	{
	case Game::GameState::MainMenu:
		RenderMainMenu();
		break;

	case Game::GameState::EscMenu:
		break;

	case Game::GameState::Level:
		break;
	}

	/*for (auto& entity : scenes[currentSceneName]->entities)
	{
		auto renderInfo = static_cast<SpriteRenderInfo*>(entity.components[Entity2D::renderInfoIndex]);
		if (renderInfo != nullptr && renderInfo.IsEnabled())
			m_window.graphics.RenderSprite(renderInfo);	
	}*/

	m_window.graphics.Present();
}

void Game::SimulateMainMenu()
{

}

void Game::RenderMainMenu()
{
	//m_window.graphics.RenderSprite();
}
