#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include "Level.h"
#include "Graphics2D.h"

class Simulator
{
public:
	Simulator(Keyboard& keyboard, Mouse& mouse, Graphics2D& graphics) noexcept;
	Simulator(const Simulator&) = delete;

	Simulator& operator=(const Simulator&) = delete;

	void Simulate(Level& level) NOEXCEPT_WHEN_NDEBUG;
	bool IsWin() const noexcept;

private:
	bool m_isWin{ false };
	float m_scrollSensitivity{ 0.1f };
	Keyboard& m_keyboard;
	Mouse& m_mouse;
	Graphics2D& m_graphics;

	Vector2f UpdateCharacterState(TiledEntity& character) const noexcept;
	void FollowCharacter(const TiledEntity& character);
	void ZoomCamera();

	static void HandleCollision(Level& level, Vector2f characterTranslation) noexcept;
	static bool AreBarrelsDelivered(Level& level) noexcept;

	static bool IsCollision(const TiledEntity& entity, const TiledEntity& otherEntity) noexcept;
	static TiledEntity* FindCollidedEntity(const Level& level, const TiledEntity& entity);
	static void ResolveCollisionWithBarrel(Level& level, TiledEntity& character,
		Vector2f characterTranslation, TiledEntity& barrel) noexcept;
};
