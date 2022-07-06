#include "Mouse.h"

#include <cmath>
#include "WinapiException.h"

std::pair<int, ScrollDirection> Mouse::GetScrollsCountAndDirection() const noexcept
{
	m_isProcessed = true;
	return { m_scrollsCount, m_scrollDirection };
}

void Mouse::OnMouseScroll(int scrollDelta) noexcept
{
	m_scrollDirection = scrollDelta < 0 ? ScrollDirection::Backward : ScrollDirection::Forward;
	m_scrollsCount = std::abs(scrollDelta / WHEEL_DELTA);
}

void Mouse::ResetState() noexcept
{
	m_scrollDirection = ScrollDirection::Forward;
	m_scrollsCount = 0;
	m_isProcessed = false;
}
