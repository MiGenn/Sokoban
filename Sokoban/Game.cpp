#include "Game.h"

#include <stdexcept>
#include <cassert>
#include "IBinarySerializable.h"

Game::Game() :
	m_window({ 1280, 720 })
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
	
	//m_currentLevel->GetCharacter().Update(m_window.keyboard);

	//if (m_currentLevel->GetCharacter().GetLastTranslation() != Vector2i())
	//{
	//	m_collisionManager.Manage(*m_currentLevel);

	//	if (CountDeliveredBarrels() == m_currentLevel->GetBarrels().size())
	//	{
	//		// win
	//	}
	//}
}

void Game::RenderMainMenu()
{

}

void Game::RenderLevel()
{
	for (auto& entity : *m_currentLevel)
		m_window.graphics.RenderSprite(entity->GetRenderInfo());
}

int Game::CountDeliveredBarrels()
{
	int deliveredBarrelsCount{ 0 };
	for (auto barrel : m_currentLevel->GetBarrels())
	{
		auto barrelPosition{ barrel->GetPosition() };
		for (auto cross : m_currentLevel->GetCrosses())
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
