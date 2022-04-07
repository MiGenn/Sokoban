#pragma once
#include "TiledEntity.h"
#include "Keyboard.h"

class Character : public TiledEntity
{
public:
	void Update(const Keyboard& keyboard);
};
