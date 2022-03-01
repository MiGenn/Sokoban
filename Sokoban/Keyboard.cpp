#include "Keyboard.h"

bool Keyboard::IsKeyPressed(unsigned char keycode) const
{
    return m_keysPressedStates[keycode];
}

void Keyboard::ResetState()
{
    m_keysPressedStates.reset();
}

void Keyboard::OnKeyDown(unsigned char keycode, bool isKeyAlreadyPressed)
{
    if (isKeyAlreadyPressed)
        m_keysPressedStates[keycode] = false;
    else
        m_keysPressedStates[keycode] = true;
}

void Keyboard::OnKeyUp(unsigned char keycode)
{
    m_keysPressedStates[keycode] = false;
}
