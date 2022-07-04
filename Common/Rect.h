#pragma once
#include "Vector2D.h"

template<Number T>
class Rect
{
public:
	Vector2D<T> topLeft;
	Vector2D<T> bottomRight;

	Rect() noexcept = default;
	Rect(Vector2D<T> topLeft, Vector2D<T> bottomRight) noexcept;
};

using RectF = Rect<float>;
using RectI = Rect<int>;

template<Number T>
inline Rect<T>::Rect(Vector2D<T> topLeft, Vector2D<T> bottomRight) noexcept
{
	this->topLeft = topLeft;
	this->bottomRight = bottomRight;
}
