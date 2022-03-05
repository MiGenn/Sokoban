#pragma once
#include "Vector2D.h"

template <typename T>
struct Box2D
{
	Vector2D<T> position;
	Vector2D<T> size;
};

typedef Box2D<float> Box2f;
typedef Box2D<int> Box2i;