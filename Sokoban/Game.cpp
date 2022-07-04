#include "Game.h"

#include <stdexcept>
#include <cassert>
#include <functional>
#include "IBinarySerializable.h"
#include "WinapiUtilities.h"
#include "PathUtilities.h"

const std::wstring Game::modulePath{ Utilities::Winapi::GetModulePath(NULL) };

Game::Game() :
	m_window({ 1280, 720 }), m_simulator(m_window.keyboard, m_window.mouse, m_window.graphics), 
	m_levelFullPaths(FindLevelFullPahts(Game::modulePath + L"Content\\Levels\\"))
{
	m_window.reloadButtonIsClicked += [this]() { ReloadCurrentLevel(); };
	m_window.loadLevelButtonIsClicked += 
		[this](const std::wstring& levelFileFullPath) { OnLoadLevelButtonClicked(levelFileFullPath); };

	std::sort(m_levelFullPaths.begin(), m_levelFullPaths.end());
	LoadNextLevel();
	if (!m_currentLevel)
		MessageBox(m_window.GetHandle(), L"The default level's folder is empty", L"Error", MB_ICONERROR);
}

int Game::Run()
{
	while (true)
	{
		if (auto exitCode = RetrieveAndRouteMessages())
			return *exitCode;

		if (m_currentLevel)
		{
			Simulate();
			Render();
		}

		WaitMessage();
	}
}

void Game::Simulate()
{
	m_simulator.Simulate(*m_currentLevel);
	if (m_simulator.IsWin())
	{
		LoadNextLevel();
		if (!m_currentLevel)
		{
			std::wstring message{ L"New levels are over. Do you want to start from the first one?" };
			if (MessageBox(m_window.GetHandle(), message.c_str(), L"", MB_OKCANCEL) == IDOK)
				LoadNextLevel();
			else
				m_levelFullPaths.clear();
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

std::vector<std::wstring> Game::FindLevelFullPahts(const std::wstring& levelFolderPath)
{
	static const std::wstring pathAndFilter(levelFolderPath + L"*.lvl");

	std::vector<std::wstring> levelFullPaths;
	WIN32_FIND_DATA findData;
	auto findHandle = FindFirstFile(pathAndFilter.c_str(), &findData);
	if (findHandle == INVALID_HANDLE_VALUE)
		return levelFullPaths;

	do
	{
		levelFullPaths.emplace_back(levelFolderPath + findData.cFileName);
	} 
	while (FindNextFile(findHandle, &findData));

	return levelFullPaths;
}

std::unique_ptr<Level> Game::LoadLevel(const std::wstring& fullPath)
{
	std::ifstream file(fullPath, std::ios::binary);
	if (!file.is_open())
	{
		MessageBox(m_window.GetHandle(), L"Cannot open the file", L"Error", MB_ICONERROR);
		return nullptr;
	}

	try
	{
		return std::make_unique<Level>(file);
	}
	catch (...)
	{
		MessageBox(m_window.GetHandle(), L"The level file is corrupted", L"Error", MB_ICONERROR);
		return nullptr;
	}
}

void Game::LoadNextLevel()
{
	if (m_nextLevelFullPathIndex >= m_levelFullPaths.size())
	{
		m_currentLevel.reset();
		m_currentLevelFullPath = nullptr;
		m_nextLevelFullPathIndex = 0ull;
		return;
	}

	m_currentLevelFullPath = &m_levelFullPaths[m_nextLevelFullPathIndex++];
	m_currentLevel = LoadLevel(*m_currentLevelFullPath);	
}

void Game::ReloadCurrentLevel()
{
	if (m_currentLevelFullPath)
		m_currentLevel = LoadLevel(*m_currentLevelFullPath);
}

void Game::OnLoadLevelButtonClicked(const std::wstring& selectedLevelFullPath)
{
	auto levelFolderPath{ Utilities::Cpp::Path::ExtractPath(selectedLevelFullPath) };
	auto levelFullPaths{ FindLevelFullPahts(levelFolderPath) };
	auto levelsCount{ (int)levelFullPaths.size() };
	if (levelsCount > 1ull)
		for (int i{ 0 }; i < levelsCount; ++i)
			if (levelFullPaths[i] == selectedLevelFullPath)
				std::swap(levelFullPaths[i], levelFullPaths[0]);

	m_levelFullPaths = std::move(levelFullPaths);
	m_nextLevelFullPathIndex = 0ull;
	LoadNextLevel();
}
