#pragma once
#include "Component.h"

class Collider : public Component
{
public:
	Collider() = default;
	Collider(const Collider&) = delete;
	Collider& operator=(const Collider&) = delete;

	void Update() override;

private:

};
