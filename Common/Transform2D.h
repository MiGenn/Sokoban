#pragma once
#include "Component.h"
#include "Vector2D.h"

class Transform2D : public Component
{
public:
	Vector2i position;

	Transform2D() = default;
	Transform2D(const Transform2D&) = delete;
	Transform2D& operator=(const Transform2D&) = delete;

	void Update() override;
};
