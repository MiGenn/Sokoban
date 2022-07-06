#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include "Level.h"
#include "Graphics2D.h"

class Simulator final
{
public:
	Simulator(const Keyboard& keyboard, const Mouse& mouse, Graphics2D& graphics) noexcept;
	Simulator(const Simulator&) = delete;

	Simulator& operator=(const Simulator&) = delete;

	void Simulate(Level& level) NOEXCEPT_WHEN_NDEBUG;
	bool IsWin() const noexcept;

private:
	bool m_isWin{ false };
	float m_scrollSensitivity{ 0.1f };
	const Keyboard& m_keyboard;
	const Mouse& m_mouse;
	Graphics2D& m_graphics;

	Vector2f UpdateCharacterState(TiledEntity& character) const noexcept;
	void FollowCharacter(const TiledEntity& character) const noexcept;
	void ZoomCamera() const noexcept;

	static void HandleCollision(Level& level, Vector2f characterTranslation) noexcept;
	static bool AreBoxesDelivered(Level& level) noexcept;

	static bool IsCollision(const TiledEntity& entity, const TiledEntity& otherEntity) noexcept;
	static TiledEntity* FindCollidedEntity(const Level& level, const TiledEntity& entity) noexcept;
	static void ResolveCollisionWithBox(Level& level, TiledEntity& character,
		Vector2f characterTranslation, TiledEntity& box) noexcept;
};
