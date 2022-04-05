#include "Mouse.h"

bool Mouse::IsLeftButtonPressed() noexcept
{
    return m_isLeftButtonPressed;
}

Vector2i Mouse::GetPosition() noexcept
{
    return m_position;
}

void Mouse::OnLeftButtonPressed() noexcept
{
    m_isLeftButtonPressed = true;
}

void Mouse::OnMouseMove(POINTS position) noexcept
{
    m_position.x = position.x;
    m_position.y = position.y;
}
