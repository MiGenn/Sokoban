#include "Game.h"

#include <stdexcept>

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
	if (!m_currentLevel)
		throw std::runtime_error("There is no loaded level!");

	m_currentLevel->characterPointer->Update(m_window.keyboard);

	if (m_currentLevel->characterPointer->GetLastTranslation() != Vector2i())
	{
		m_collisionManager.Manage(*m_currentLevel);

		if (CountDeliveredBarrels() == m_currentLevel->barrelsPointers.size())
		{
			// win
		}
	}
}

void Game::RenderMainMenu()
{

}

void Game::RenderLevel()
{
	for (auto entity : m_currentLevel->entities)
		m_window.graphics.RenderSprite(entity->GetRenderInfo());
}

int Game::CountDeliveredBarrels()
{
	int deliveredBarrelsCount{ 0 };
	for (auto barrel : m_currentLevel->barrelsPointers)
	{
		auto barrelPosition{ barrel->GetPosition() };
		for (auto cross : m_currentLevel->crossesPointers)
		{
			if (barrelPosition == cross->GetPosition())
			{
				++deliveredBarrelsCount;
				break;
			}
		}
	}

	return deliveredBarrelsCount;
}
