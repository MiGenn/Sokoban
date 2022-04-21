#include "Keyboard.h"

#include "WinapiException.h"

bool Keyboard::IsKeyPressed(unsigned char keycode) noexcept
{
    m_isProcessed = true;
    return m_keysPressedStates[keycode];
}

bool Keyboard::IsProcessed() const noexcept
{
    return m_isProcessed;
}

void Keyboard::ResetState() noexcept
{
    m_keysPressedStates.reset();
    m_isProcessed = false;
}

void Keyboard::OnKeyDown(unsigned char keycode, bool isKeyAlreadyPressed) noexcept
{
    if (isKeyAlreadyPressed)
    {
        m_keysPressedStates[keycode] = false;
    }
    else
    {
        m_keysPressedStates[keycode] = true;
    }
}

void Keyboard::OnKeyUp(unsigned char keycode) noexcept
{
    m_keysPressedStates[keycode] = false;
}
