#include "LevelCollisionManager.h"

void LevelCollisionManager::SetLevel(Level* level)
{
	m_level = level;
}

void LevelCollisionManager::Update()
{
	Vector2i characterPosition{ m_level->character->GetPosition() };
	for (auto entity : m_level->entities)
	{
		if (characterPosition == entity->GetPosition())
		{
			if (entity->IsMovable())
			{
				Vector2i translation{ characterPosition - m_level->character->GetPreviousPosition() };
				entity->Move(translation);

				for (auto entity2 : m_level->entities)
				{
					if (entity->IsCollision(*entity2) && entity != entity2)
					{
						entity->Move(-translation);
						m_level->character->Move(-translation);
						
						break;
					}
				}
			}
			else
			{
				m_level->character->Move(-m_level->character->GetPreviousPosition());
			}
		}
	}
}
