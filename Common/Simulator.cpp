#include "Simulator.h"

Simulator::Simulator(Keyboard& keyboard, Mouse& mouse) noexcept :
	m_keyboard(keyboard), m_mouse(mouse)
{

}

void Simulator::Simulate(Level& level) NOEXCEPT_WHEN_NDEBUG
{
	assert(level.GetCharacter() != nullptr);
	auto characterTranslation{ UpdateCharacter(*level.GetCharacter()) };
	HandleCollision(level, characterTranslation);
	m_isWin = AreAllBarrelsDelivered(level);
}

bool Simulator::IsWin() const noexcept
{
	return m_isWin;
}

Vector2i Simulator::UpdateCharacter(TiledEntity& character ) const noexcept
{
	Vector2i translation;

	if (m_keyboard.IsKeyPressed('W'))
		translation += Vector2i(0, -1);
	else if (m_keyboard.IsKeyPressed('S'))
		translation += Vector2i(0, 1);
	else if (m_keyboard.IsKeyPressed('A'))
		translation += Vector2i(-1, 0);
	else if (m_keyboard.IsKeyPressed('D'))
		translation += Vector2i(1, 0);

	character.Move(translation);
	return translation;
}

void Simulator::HandleCollision(Level& level, Vector2i characterTranslation) noexcept
{
	auto& character{ *level.GetCharacter() };
	auto collidedEntity{ FindCollidedEntity(level, character) };
	if (collidedEntity)
	{
		switch (collidedEntity->GetTag())
		{
		case TiledEntity::Tag::Barrel:
			ResolveCollisionWithBarrel(level, character, characterTranslation, *collidedEntity);
			break;

		case TiledEntity::Tag::Wall:
			character.Move(-characterTranslation);
			break;
		}
	}
}

bool Simulator::AreAllBarrelsDelivered(Level& level) noexcept
{
	int deliveredBarrelsCount{ 0 };
	for (auto barrel : level.GetBarrels())
	{
		for (auto cross : level.GetCrosses())
		{
			if (barrel->GetPosition() == cross->GetPosition())
			{
				++deliveredBarrelsCount;
				break;
			}
		}
	}

	return deliveredBarrelsCount == level.GetBarrels().size();
}

bool Simulator::IsCollision(const TiledEntity& entity, const TiledEntity& otherEntity) noexcept
{
	return entity.GetPosition() == otherEntity.GetPosition() &&
		!Level::CanEntitiesBeInTheSamePosition(entity, otherEntity) &&
		&entity != &otherEntity;
}

TiledEntity* Simulator::FindCollidedEntity(const Level& level, const TiledEntity& entity)
{
	auto collidedEntityIterator{ std::find_if(level.begin(), level.end(),
		[&entity](const std::unique_ptr<TiledEntity>& otherEntity)
		{
			return IsCollision(entity, *otherEntity);
		}) };

	if (collidedEntityIterator == level.end())
		return nullptr;

	return collidedEntityIterator->get();
}

void Simulator::ResolveCollisionWithBarrel(Level& level, TiledEntity& character,
	Vector2i characterTranslation, TiledEntity& barrel) noexcept
{
	barrel.Move(characterTranslation);
	auto collidedEntity{ FindCollidedEntity(level, barrel) };
	if (collidedEntity)
	{
		barrel.Move(-characterTranslation);
		character.Move(-characterTranslation);
	}
}
