#include "Game.h"

#include <stdexcept>
#include <cassert>
#include <functional>
#include "IBinarySerializable.h"
#include "WinapiUtilities.h"
#include "PathUtilities.h"

const std::wstring Game::modulePath{ Utilities::Winapi::GetModulePath(nullptr) };

Game::Game() :
	m_window({ 1280, 720 }), m_simulator(m_window.keyboard, m_window.mouse, m_window.graphics), 
	m_levelFullPaths(FindLevelFullPahts(Game::modulePath + L"Content\\Levels\\"))
{
	m_window.reloadButtonIsClicked += [this]() { ReloadCurrentLevel(); };
	m_window.loadLevelButtonIsClicked += 
		[this](const std::wstring& levelFileFullPath) { OnLoadLevelButtonClicked(levelFileFullPath); };

	m_currentLevel = LoadNextLevel();
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

void Game::Simulate() NOEXCEPT_WHEN_NDEBUG
{
	m_simulator.Simulate(*m_currentLevel);
	if (m_simulator.IsWin())
	{
		auto nextLevel{ LoadNextLevel() };
		if (!(isGameOver = !nextLevel))
			m_currentLevel = std::move(nextLevel);
	}
}

void Game::Render()
{	
	for (auto& entity : *m_currentLevel)
		m_window.graphics.RenderSprite(entity->GetRenderInfo());

	m_window.graphics.Present();
	m_window.graphics.Clear(RGB(140, 115, 60));

	if (isGameOver)
	{
		std::wstring message{ L"New levels are over. Do you want to start from the first one?" };
		if (MessageBox(m_window.GetHandle(), message.c_str(), L"", MB_OKCANCEL) == IDOK)
		{
			m_currentLevel = LoadNextLevel();
		}
		else
		{
			m_levelFullPaths.clear();
			m_currentLevel.reset();
		}

		isGameOver = false;
		m_window.graphics.Present();
	}
}

std::vector<std::wstring> Game::FindLevelFullPahts(const std::wstring& levelFolderPath) noexcept
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

	std::sort(levelFullPaths.begin(), levelFullPaths.end(),
		[](const std::wstring& first, const std::wstring& second)
		{
			return first.size() < second.size();
		});

	return levelFullPaths;
}

std::unique_ptr<Level> Game::LoadLevel(const std::wstring& fullPath) const noexcept
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

std::unique_ptr<Level> Game::LoadNextLevel() noexcept
{
	static std::wstring* currentLevelFullPath{ nullptr };

	if (m_nextLevelFullPathIndex >= m_levelFullPaths.size())
	{
		currentLevelFullPath = nullptr;
		m_nextLevelFullPathIndex = 0ull;
		return nullptr;
	}

	currentLevelFullPath = &m_levelFullPaths[m_nextLevelFullPathIndex++];
	return LoadLevel(*currentLevelFullPath);
}

void Game::ReloadCurrentLevel() noexcept
{
	if (m_nextLevelFullPathIndex > 0)
		--m_nextLevelFullPathIndex;
	
	m_currentLevel = LoadNextLevel();
}

void Game::OnLoadLevelButtonClicked(const std::wstring& selectedLevelFullPath) noexcept
{
	auto levelFolderPath{ Utilities::Cpp::Path::ExtractPath(selectedLevelFullPath) };
	auto levelFullPaths{ FindLevelFullPahts(levelFolderPath) };
	auto levelsCount{ (int)levelFullPaths.size() };
	for (int i{ 0 }; i < levelsCount; ++i)
	{
		if (levelFullPaths[i] == selectedLevelFullPath)
		{
			m_nextLevelFullPathIndex = i;
			break;
		}
	}

	m_levelFullPaths = std::move(levelFullPaths);
	m_currentLevel = LoadNextLevel();
}
