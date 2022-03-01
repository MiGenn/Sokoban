#pragma once
#include <string>
#include "Application.h"
#include "Scene.h"
#include "GameWindow.h"

class Game final : public Application
{
public:
	Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	int Run() override;

private:
	GameWindow m_window;
	std::vector<Scene*> m_scenes;

	void Simulate();
	void Render();

	//void LoadScene(const std::wstring& file);
};
