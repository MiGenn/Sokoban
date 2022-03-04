#pragma once
#include <string>
#include "Application.h"
#include "Level.h"
#include "LevelLoader.h"
#include "GameWindow.h"

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

	GameState m_state = GameState::MainMenu;
	GameWindow m_window;

	Level* m_currentLevel;
	//Character m_character;

	void Simulate();
	void Render();

	void SimulateMainMenu();

	void RenderMainMenu();
};
