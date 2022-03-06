#pragma once
#include "Level.h"

class LevelCollisionManager
{
public:
	void SetLevel(Level* level);

	void Update();

private:
	Level* m_level = nullptr;
};
