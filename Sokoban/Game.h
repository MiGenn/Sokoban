#pragma once
#include "Application.h"
#include "GameWindow.h"
#include "Simulator.h"

class Game final : public Application
{
public:
	Game();
	Game(const Game&) = delete;

	Game& operator=(const Game&) = delete;

	int Run() override;

private:
	enum class GameState : char
	{
		MainMenu,
		EscMenu,
		Level
	};

	GameWindow m_window;

	GameState m_state = GameState::MainMenu;
	// Menu
	Simulator m_simulator;
	std::unique_ptr<Level> m_currentLevel;

	void Simulate();
	void Render();

	void SimulateMainMenu();
	void SimulateLevel();

	void RenderMainMenu();
	void RenderLevel();
};
