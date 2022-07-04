#pragma once
#include <Rect.h>

class Collision2D final
{
public:
	Collision2D() = delete;
	Collision2D(const Collision2D&) = delete;

	Collision2D& operator=(const Collision2D&) = delete;

	static bool IsCollision(Vector2f firstRectPosition, Vector2f firstRectSize,
		Vector2f secondRectPosition, Vector2f secondRectSize) noexcept;
	static bool IsCollision(const RectF& firstRect, const RectF& secondRect) noexcept;
};
