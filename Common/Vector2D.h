#pragma once

template<typename T>
class Vector2D final
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

	bool operator==(const Vector2D<T>& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	bool operator!=(const Vector2D<T>& rhs) const
	{
		return !((*this) == rhs);
	}

	Vector2D<T> operator-()
	{
		return { -x, -y };
	}

	Vector2D<T> operator+(const Vector2D<T>& rhs) const
	{
		return { x + rhs.x, y + rhs.y };
	}

	Vector2D<T>& operator+=(const Vector2D<T>& rhs)
	{
		return (*this) = (*this) + rhs;
	}

	Vector2D<T> operator-(const Vector2D<T>& rhs) const
	{
		return { x - rhs.x, y - rhs.y };
	}

	Vector2D<T>& operator-=(const Vector2D<T>& rhs)
	{
		return (*this) = (*this) - rhs;
	}
};

typedef Vector2D<float> Vector2f;
typedef Vector2D<int> Vector2i;