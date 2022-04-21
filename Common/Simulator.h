#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include "Level.h"

class Simulator
{
public:
	Simulator(Keyboard& keyboard, Mouse& mouse) noexcept;
	Simulator(const Simulator&) = delete;

	Simulator& operator=(const Simulator&) = delete;

	void Simulate(Level& level) NOEXCEPT_WHEN_NDEBUG;
	bool IsWin() const noexcept;

private:
	bool m_isWin{ false };
	Keyboard& m_keyboard;
	Mouse& m_mouse;

	Vector2i UpdateCharacter(TiledEntity& character) const noexcept;
	static void HandleCollision(Level& level, Vector2i characterTranslation) noexcept;
	static bool AreAllBarrelsDelivered(Level& level) noexcept;

	static bool IsCollision(const TiledEntity& entity, const TiledEntity& otherEntity) noexcept;
	static TiledEntity* FindCollidedEntity(const Level& level, const TiledEntity& entity);
	static void ResolveCollisionWithBarrel(Level& level, TiledEntity& character,
		Vector2i characterTranslation, TiledEntity& barrel) noexcept;
};
