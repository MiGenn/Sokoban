#pragma once
#include <optional>
#include "WindowClass.h"
#include "Graphics2D.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Event.h"

class Game;

class GameWindow final : public Window
{
public:
	Utilities::Cpp::Event<> reloadButtonIsClicked;
	Utilities::Cpp::Event<std::wstring> loadLevelButtonIsClicked;

	Mouse mouse;
	Keyboard keyboard;
	Graphics2D graphics;

	GameWindow(Vector2i size);
	GameWindow(const GameWindow&) = delete;

	GameWindow& operator=(const GameWindow&) = delete;

	void Resize(Vector2i size) override;

private:
	enum class HotKey
	{
		Restart
	};

	static constexpr const wchar_t* m_levelFilter{ L"Level Files\0*.lvl\0" };

	LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam) override;

	void OnClose() noexcept;
	void OnCommand(int controlID);

	void OnRestartButtonClick();
	void OnLoadLevelButtonClick();
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
