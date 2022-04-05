#include "DeviceContextWrapper.h"

#include <cassert>

DeviceContextWrapper::DeviceContextWrapper(const Window* window) NOEXCEPT_WHEN_NDEBUG :
	m_window(window), m_windowContext(GetDC(window->GetHandle()))
{
	assert(window != nullptr);
}

DeviceContextWrapper::~DeviceContextWrapper() noexcept
{
	ReleaseDC(m_window->GetHandle(), m_windowContext);
}

HDC DeviceContextWrapper::Get() const noexcept
{
	return m_windowContext;
}
