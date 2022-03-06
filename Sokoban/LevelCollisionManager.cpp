#include "LevelCollisionManager.h"

void LevelCollisionManager::Manage(Level& level)
{
	auto entity{ GetEntityCollidingWithCharacter(level) };
	if (entity)
	{
		if (entity->IsMovable())
		{
			Vector2i translation{ level.character->GetPosition() - level.character->GetPreviousPosition() };
			entity->Move(translation);

			if (IsEntityInCollision(level, *entity))
			{
				entity->Move(-translation);
				level.character->RevertToPreviousPosition();
			}
		}
		else if (entity->IsCollidable())
		{
			level.character->RevertToPreviousPosition();
		}
	}
}

TiledEntity* LevelCollisionManager::GetEntityCollidingWithCharacter(const Level& level) const
{
	for (auto entity : m_level->entities)
		if (m_level->character->IsCollision(*entity))
			return entity;

	return nullptr;
}

bool LevelCollisionManager::IsEntityInCollision(const Level& level, const TiledEntity& entity) const
{
	for (auto otherEntity : m_level->entities)
		if (entity.IsCollision(*otherEntity) && entity != *otherEntity)
			return true;

	return false;
}
