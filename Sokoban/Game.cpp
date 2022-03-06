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

	static Vector2i translation;

	if (m_window.keyboard.IsKeyPressed('W'))
		translation += Vector2i(0, -1);

	if (m_window.keyboard.IsKeyPressed('S'))
		translation += Vector2i(0, 1);

	if (m_window.keyboard.IsKeyPressed('A'))
		translation += Vector2i(-1, 0);

	if (m_window.keyboard.IsKeyPressed('D'))
		translation += Vector2i(1, 0);

	if (translation != Vector2i())
		m_levelCollisionManager.Manage(*m_currentLevel);
}

void Game::RenderMainMenu()
{

}

void Game::RenderLevel()
{
	m_window.graphics.RenderSprite(m_currentLevel->character->GetRenderInfo());

	for (auto entity : m_currentLevel->entities)
		m_window.graphics.RenderSprite(entity->GetRenderInfo());
}
