#include "Game.h"

#include <stdexcept>
#include <cassert>
#include <functional>
#include "IBinarySerializable.h"
#include "WinapiUntilities.h"

const std::wstring Game::ModulePath{ WinapiUntilities::GetModulePath(NULL) };

Game::Game() :
	m_window({ 1280, 720 }), m_simulator(m_window.keyboard), 
	m_levelsFullPaths(FindLevelsFullPahts())
{
	
}

int Game::Run()
{
	m_window.SubscribeToRestartButtonClick([this]() 
		{
			this->ReloadCurrentLevel();
		});
	LoadNextLevel();

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
	assert(m_currentLevel != nullptr);
	m_simulator.Simulate(*m_currentLevel);
	if (m_simulator.IsWin())
	{
		LoadNextLevel();
		if (m_currentLevel == nullptr)
		{
			MessageBox(m_window.GetHandle(), L"You beat the game", L"", MB_OK);
			SendMessage(m_window.GetHandle(), WM_CLOSE, NULL, NULL);
		}
	}
}

void Game::Render()
{
	m_window.graphics.Clear(RGB(0, 128, 0));
	for (auto& entity : *m_currentLevel)
		m_window.graphics.RenderSprite(entity->GetRenderInfo());

	m_window.graphics.Present();	
}

std::vector<std::wstring> Game::FindLevelsFullPahts()
{
	static const std::wstring levelPath(Game::ModulePath + L"Content\\Levels\\");
	static const std::wstring pathAndFilter(levelPath + L"*.lvl");

	std::vector<std::wstring> levelsFullPaths;
	WIN32_FIND_DATA findData;
	auto findHandle = FindFirstFile(pathAndFilter.c_str(), &findData);
	if (findHandle == INVALID_HANDLE_VALUE)
		throw WINAPI_LAST_EXCEPTION();

	do
	{
		levelsFullPaths.emplace_back(levelPath + findData.cFileName);
	} 
	while (FindNextFile(findHandle, &findData));
	std::sort(levelsFullPaths.begin(), levelsFullPaths.end());

	return levelsFullPaths;
}

std::unique_ptr<Level> Game::LoadLevel(const std::wstring& fullPath)
{
	std::ifstream file(fullPath, std::ios::binary);
	if (!file.is_open())
	{
		throw std::runtime_error("Cannot open the level file");
	}

	try
	{
		return std::make_unique<Level>(file);
	}
	catch (...)
	{
		throw std::runtime_error("The level file is corrupted");
	}
}

void Game::LoadNextLevel()
{
	static int fullPathIndex{ 0 };
	if (fullPathIndex >= m_levelsFullPaths.size())
	{
		m_currentLevel.reset();
		return;
	}

	m_currentLevelFullPath = &m_levelsFullPaths[fullPathIndex++];
	m_currentLevel = LoadLevel(*m_currentLevelFullPath);	
}

void Game::ReloadCurrentLevel()
{
	m_currentLevel = LoadLevel(*m_currentLevelFullPath);
}
