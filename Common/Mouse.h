#pragma once
#include <utility>

enum class ScrollDirection
{
	Forward = 1,
	Backward = -1
};

class Mouse final
{
public:
	friend class GameWindow;
	friend class EditorWindow;

	Mouse() noexcept = default;
	Mouse(const Mouse&) = delete;

	Mouse& operator=(const Mouse&) = delete;

	std::pair<int, ScrollDirection> GetScrollsCountAndDirection() const noexcept;

private:
	ScrollDirection m_scrollDirection;
	int m_scrollsCount{ 0 };
	
	mutable bool m_isProcessed{ false };

	void ResetState() noexcept;
	void OnMouseScroll(int scrollDelta) noexcept;
};
