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

	Mouse() = default;
	Mouse(const Mouse&) = delete;

	Mouse& operator=(const Mouse&) = delete;

	std::pair<int, ScrollDirection> GetScrollsCountAndDirection();

private:
	ScrollDirection m_scrollDirection;
	int m_scrollsCount{ 0 };
	
	bool m_isProcessed{ false };

	void OnMouseScroll(int scrollDelta);
	void ResetState();
};
