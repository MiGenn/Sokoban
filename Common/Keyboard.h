#pragma once
#include <bitset>

class Keyboard final
{
public:
	friend class GameWindow;
	friend class EditorWindow;

	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;

	Keyboard& operator=(const Keyboard&) = delete;

	bool IsKeyPressed(unsigned char keycode) noexcept;

private:
	static constexpr size_t m_keysNumber{ 256ull };

	std::bitset<m_keysNumber> m_keysPressedStates;
	bool m_isProcessed{ false };

	bool IsProcessed() const noexcept;
	void ResetState() noexcept;
	void OnKeyDown(unsigned char keycode, bool isKeyAlreadyPressed) noexcept;
	void OnKeyUp(unsigned char keycode) noexcept;
};
