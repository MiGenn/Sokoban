#include "DeviceContextWrapper.h"

DeviceContextWrapper::DeviceContextWrapper(const Window* window) :
	m_window(window), m_windowContext(GetDC(window->GetHandle()))
{
	 
}

DeviceContextWrapper::~DeviceContextWrapper()
{
	ReleaseDC(m_window->GetHandle(), m_windowContext);
}

HDC DeviceContextWrapper::Get() const
{
	return m_windowContext;
}
