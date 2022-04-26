#pragma once
#include <optional>
#include "WindowClass.h"
#include "Graphics2D.h"
#include "Keyboard.h"

class Game;

class GameWindow final : public Window
{
public:
	Keyboard keyboard;
	Graphics2D graphics;

	GameWindow(Vector2i size);
	GameWindow(const GameWindow&) = delete;

	GameWindow& operator=(const GameWindow&) = delete;

	void Resize(Vector2i size) override;
	void SubscribeToRestartButtonClick(std::function<void()> onFunction);

private:
	enum class HotKey
	{
		Restart
	};

	std::vector<std::function<void()>> m_subscribedFunctions;

	LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam) override;

	void OnClose() noexcept;
	void OnCommand(int controlID);

	void OnRestartButtonClick();
	void OnHotKey(HotKey hotKey);

	class Class final : public WindowClass
	{
	public:
		static const Class gameWindow;

	private:
		Class();
		Class(const Class&) = delete;
		Class& operator=(const Class&) = delete;
	};
};
