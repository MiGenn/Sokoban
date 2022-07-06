#include "WindowDC.h"

#include <cassert>
#include "Window.h"

Utilities::Winapi::SmartPointer::WindowDC::WindowDC(const Window* window) NOEXCEPT_WHEN_NDEBUG :
	m_window(window)
{
	assert(window);
	m_windowContext = GetDC(window->GetHandle());
}

Utilities::Winapi::SmartPointer::WindowDC::~WindowDC() noexcept
{
	ReleaseDC(m_window->GetHandle(), m_windowContext);
}

HDC Utilities::Winapi::SmartPointer::WindowDC::Get() const noexcept
{
	return m_windowContext;
}
