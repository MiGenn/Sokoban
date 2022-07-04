#include "Simulator.h"

Simulator::Simulator(Keyboard& keyboard, Mouse& mouse, Graphics2D& graphics) noexcept :
	m_keyboard(keyboard), m_mouse(mouse), m_graphics(graphics)
{

}

void Simulator::Simulate(Level& level) NOEXCEPT_WHEN_NDEBUG
{
	auto* character{ level.GetCharacter() };
	assert(character);

	auto characterTranslation{ UpdateCharacterState(*character) };
	HandleCollision(level, characterTranslation);
	FollowCharacter(*character);
	ZoomCamera();
	m_isWin = AreBarrelsDelivered(level);
}

bool Simulator::IsWin() const noexcept
{
	return m_isWin;
}

Vector2f Simulator::UpdateCharacterState(TiledEntity& character) const noexcept
{
	Vector2f translation;

	if (m_keyboard.IsKeyPressed('W'))
		translation = Vector2f(0.f, 1.f);
	else if (m_keyboard.IsKeyPressed('S'))
		translation = Vector2f(0.f, -1.f);
	else if (m_keyboard.IsKeyPressed('A'))
		translation = Vector2f(-1.f, 0.f);
	else if (m_keyboard.IsKeyPressed('D'))
		translation = Vector2f(1.f, 0.f);
	
	character.Move(translation);
	return translation;
}

void Simulator::FollowCharacter(const TiledEntity& character)
{
	auto halfCharacterSize{ (Vector2f)character.GetRenderInfo().GetSize() / 2.f };
	halfCharacterSize.y *= -1.f;
	Vector2f cameraPosition{ character.GetPosition() + halfCharacterSize };
	m_graphics.SetCameraPosition(cameraPosition);
}

void Simulator::ZoomCamera()
{
	static constexpr auto zoomMin{ 0.5f };
	static constexpr auto zoomMax{ 10.f };

	auto zoom{ m_graphics.GetZoom() };
	auto scrollsCountAndDirection{ m_mouse.GetScrollsCountAndDirection() };

	while (scrollsCountAndDirection.first > 0)
	{
		zoom += zoom * m_scrollSensitivity * (int)scrollsCountAndDirection.second;
		--scrollsCountAndDirection.first;
	}

	zoom = std::clamp(zoom, zoomMin, zoomMax);
	m_graphics.SetZoom(zoom);
}

void Simulator::HandleCollision(Level& level, Vector2f characterTranslation) noexcept
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

bool Simulator::AreBarrelsDelivered(Level& level) noexcept
{
	auto deliveredBarrelsCount{ 0 };
	for (auto barrel : level.GetBarrels())
	{
		for (auto cross : level.GetCrosses())
		{
			if (barrel->IsCollision(*cross))
			{
				++deliveredBarrelsCount;
				break;
			}
		}
	}

	return deliveredBarrelsCount == (int)level.GetBarrels().size();
}

bool Simulator::IsCollision(const TiledEntity& entity, const TiledEntity& otherEntity) noexcept
{
	return entity.IsCollision(otherEntity) &&
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
	Vector2f characterTranslation, TiledEntity& barrel) noexcept
{
	barrel.Move(characterTranslation);
	auto collidedEntity{ FindCollidedEntity(level, barrel) };
	if (collidedEntity)
	{
		barrel.Move(-characterTranslation);
		character.Move(-characterTranslation);
	}
}
