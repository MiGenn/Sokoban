#include "Character.h"

void Character::Update(const Keyboard& keyboard)
{
	static Vector2i translation;

	if (keyboard.IsKeyPressed('W'))
		translation += Vector2i(0, -1);

	if (keyboard.IsKeyPressed('S'))
		translation += Vector2i(0, 1);

	if (keyboard.IsKeyPressed('A'))
		translation += Vector2i(-1, 0);

	if (keyboard.IsKeyPressed('D'))
		translation += Vector2i(1, 0);

	Move(translation);
}
