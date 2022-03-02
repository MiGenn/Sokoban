#include "Object.h"

bool Object::IsEnabled() const
{
    return m_isEnabled;
}

bool Object::Enable()
{
    return m_isEnabled = true;
}

bool Object::Disable()
{
    return m_isEnabled = false;
}
