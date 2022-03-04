#include "Mouse.h"

bool Mouse::IsLeftButtonPressed()
{
    return m_isLeftButtonPressed;
}

Vector2i Mouse::GetPosition()
{
    return m_position;
}

void Mouse::OnLeftButtonPressed()
{
    m_isLeftButtonPressed = true;
}

void Mouse::OnMouseMove(POINTS position)
{
    m_position.x = position.x;
    m_position.y = position.y;
}
