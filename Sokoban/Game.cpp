#include "Game.h"

#include <stdexcept>
#include <cassert>
#include "IBinarySerializable.h"

Game::Game() :
	m_window({ 1280, 720 }), m_simulator(m_window.keyboard, m_window.mouse)
{
	
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
		SimulateLevel();
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
		RenderLevel();
		break;
	}

	m_window.graphics.Present();
}

void Game::SimulateMainMenu()
{

}

void Game::SimulateLevel()
{
	assert(m_currentLevel.get() != nullptr);
	m_simulator.Simulate(*m_currentLevel);
	if (m_simulator.IsWin())
	{

	}
}

void Game::RenderMainMenu()
{

}

void Game::RenderLevel()
{
	for (auto& entity : *m_currentLevel)
		m_window.graphics.RenderSprite(entity->GetRenderInfo());
}
