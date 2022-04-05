#include "CollisionManager.h"

void CollisionManager::Manage(Level& level)
{
	auto entity{ GetEntityCollidingWithCharacter(level) };
	if (entity)
	{
		if (entity->IsMovable())
		{
			Vector2i translation{ level.characterPointer->GetLastTranslation() };
			entity->Move(translation);

			if (IsEntityInCollision(level, *entity))
			{
				entity->Move(-translation);
				level.characterPointer->RevertToPreviousPosition();
			}
		}
		else if (entity->IsCollidable())
		{
			level.characterPointer->RevertToPreviousPosition();
		}
	}
}

TiledEntity* CollisionManager::GetEntityCollidingWithCharacter(const Level& level) const
{
	//for (auto entity : level.entities)
	//	if (level.characterPointer->IsCollision(*entity))
	//		return entity;

	return nullptr;
}

bool CollisionManager::IsEntityInCollision(const Level& level, const TiledEntity& entity) const
{
	//for (auto otherEntity : level.entities)
	//	if (entity.IsCollision(*otherEntity) && entity != *otherEntity)
	//		return true;

	return false;
}
