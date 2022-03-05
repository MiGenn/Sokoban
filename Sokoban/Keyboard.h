#pragma once
#include <bitset>

class Keyboard final
{
public:
	friend class GameWindow;

	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;

	Keyboard& operator=(const Keyboard&) = delete;

	bool IsKeyPressed(unsigned char keycode) const;

private:
	static constexpr size_t m_keysNumber{ 256ull };

	std::bitset<m_keysNumber> m_keysPressedStates;

	void ResetState();
	void OnKeyDown(unsigned char keycode, bool isKeyAlreadyPressed);
	void OnKeyUp(unsigned char keycode);
};
