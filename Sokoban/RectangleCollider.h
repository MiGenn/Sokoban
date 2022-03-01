#pragma once
#include "Collider.h"

class RectangleCollider : public Collider
{
public:
	RectangleCollider() = default;
	RectangleCollider(const RectangleCollider&) = delete;
	RectangleCollider& operator=(const RectangleCollider&) = delete;
};
