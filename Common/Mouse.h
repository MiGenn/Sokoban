#pragma once
#include "Vector2D.h"
#include "WinapiException.h"

class Mouse final
{
public:
	friend class GameWindow;
	friend class EditorWindow;

	bool IsLeftButtonPressed() noexcept;
	Vector2i GetPosition() noexcept;

private:
	Vector2i m_position;
	bool m_isLeftButtonPressed;

	void OnLeftButtonPressed() noexcept;
	void OnMouseMove(POINTS position) noexcept;
};
