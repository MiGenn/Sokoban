#pragma once
#include "Application.h"
#include "GameWindow.h"
#include "Level.h"
#include "LevelLoader.h"
#include "LevelCollisionManager.h"

class Game final : public Application
{
public:
	Game();
	Game(const Game&) = delete;
	~Game();

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
	LevelCollisionManager m_levelCollisionManager;
	// Menu
	Level* m_currentLevel = nullptr;

	void Simulate();
	void Render();

	void SimulateMainMenu();
	void SimulateLevel();

	void RenderMainMenu();
	void RenderLevel();
};
