#include "WindowDCWrapper.h"

#include <cassert>

WindowDCWrapper::WindowDCWrapper(const Window* window) NOEXCEPT_WHEN_NDEBUG :
	m_window(window), m_windowContext(GetDC(window->GetHandle()))
{
	assert(window != nullptr);
}

WindowDCWrapper::~WindowDCWrapper() noexcept
{
	ReleaseDC(m_window->GetHandle(), m_windowContext);
}

HDC WindowDCWrapper::Get() const noexcept
{
	return m_windowContext;
}
