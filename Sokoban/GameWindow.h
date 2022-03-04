#pragma once
#include <optional>
#include "WindowClass.h"
#include "Graphics2D.h"
#include "Mouse.h"
#include "Keyboard.h"

class GameWindow final : public Window
{
public:
	Mouse mouse;
	Keyboard keyboard;
	Graphics2D graphics;

	GameWindow(int width, int height);
	GameWindow(const GameWindow&) = delete;

	GameWindow& operator=(const GameWindow&) = delete;

private:
	LRESULT HandleMessages(UINT message, WPARAM wParam, LPARAM lParam) override;

	void OnClose();

	class Class : public WindowClass
	{
	public:
		static const Class gameWindow;

	private:
		Class();
		Class(const Class&) = delete;
		Class& operator=(const Class&) = delete;
	};
};
