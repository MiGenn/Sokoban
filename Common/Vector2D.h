#pragma once

template<typename T>
class Vector2D
{
public:
	T x = T();
	T y = T();

	Vector2D() = default;
	Vector2D(T x, T y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2D<T> operator+(const Vector2D<T>& rhs) const
	{
		return { x + rhs.x, y + rhs.y };
	}

	//static constexpr Vector2i up{ 0, 0 };
};

typedef Vector2D<float> Vector2f;
typedef Vector2D<int> Vector2i;