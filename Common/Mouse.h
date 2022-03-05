#pragma once
#include "Vector2D.h"
#include "WinapiException.h"

class Mouse final
{
public:
	friend class GameWindow;
	friend class EditorWindow;

	bool IsLeftButtonPressed();
	Vector2i GetPosition();

private:
	Vector2i m_position;
	bool m_isLeftButtonPressed;

	void OnLeftButtonPressed();
	void OnMouseMove(POINTS position);
};
