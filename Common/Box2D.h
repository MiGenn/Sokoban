#pragma once
#include "Vector2D.h"

template <typename T>
class Box2D
{
public:
	Box2D()
	{

	}

	Box2D(Vector2D<T> position, Vector2D<T> size)
	{
		SetPosition(position);
		SetSize(size);
	}

	void SetPosition(Vector2D<T> newPosition) noexcept
	{
		m_position = newPosition;
	}

	void SetSize(Vector2D<T> newSize)
	{
		if (newSize.x <= 0 || newSize.y <= 0)
			throw std::logic_error("The size is incorrect!");
	}

	Vector2D<T> GetSize() const noexcept
	{
		return m_size;
	}

	Vector2D<T> GetPosition() const noexcept
	{
		return m_position;
	}

private:
	Vector2D<T> m_position;
	Vector2D<T> m_size;
};

typedef Box2D<float> Box2f;
typedef Box2D<int> Box2i;