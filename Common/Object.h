#pragma once

class Object
{
public:
	bool IsEnabled() const;
	bool Enable();
	bool Disable();

private:
	bool m_isEnabled = true;
};
