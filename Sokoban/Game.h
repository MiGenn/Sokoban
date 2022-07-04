#pragma once
#include "Application.h"
#include "GameWindow.h"
#include "Simulator.h"

class Game final : public Application
{
public:
	static const std::wstring modulePath;

	Game();
	Game(const Game&) = delete;

	Game& operator=(const Game&) = delete;

	int Run() override;

private:
	GameWindow m_window;
	Simulator m_simulator;

	std::unique_ptr<Level> m_currentLevel;
	const std::wstring* m_currentLevelFullPath;
	size_t m_nextLevelFullPathIndex{ 0ull };
	std::vector<std::wstring> m_levelFullPaths;

	void Simulate();
	void Render();

	std::vector<std::wstring> FindLevelFullPahts(const std::wstring& levelFolderPath);
	std::unique_ptr<Level> LoadLevel(const std::wstring& fullPath);
	void LoadNextLevel();
	void ReloadCurrentLevel();
	void OnLoadLevelButtonClicked(const std::wstring& levelFileFullPath);
};
