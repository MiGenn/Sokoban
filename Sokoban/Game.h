#pragma once
#include "Application.h"
#include "GameWindow.h"
#include "Simulator.h"

class Game final : public Application
{
public:
	static const std::wstring ModulePath;

	Game();
	Game(const Game&) = delete;

	Game& operator=(const Game&) = delete;

	int Run() override;

private:
	GameWindow m_window;

	Simulator m_simulator;
	std::unique_ptr<Level> m_currentLevel;
	const std::wstring* m_currentLevelFullPath;
	const std::vector<std::wstring> m_levelsFullPaths;

	void Simulate();
	void Render();

	std::vector<std::wstring> FindLevelsFullPahts();
	std::unique_ptr<Level> LoadLevel(const std::wstring& fullPath);
	void LoadNextLevel();
	void ReloadCurrentLevel();
};
