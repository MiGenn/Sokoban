#include "Window.h"

#include <cassert>
#include "WindowDC.h"

Window::Window(Vector2i size) NOEXCEPT_WHEN_NDEBUG :
	m_size(size)
{
	assert(size.x > 0 && size.y > 0);
}

void Window::Resize(Vector2i size)
{
	assert(size.x > 0 && size.y > 0);
	if (!SetWindowPos(m_handle, nullptr, NULL, NULL, size.x, size.y, SWP_NOMOVE | SWP_NOZORDER))
		throw WINAPI_LAST_EXCEPTION();
	
	m_size = size;
}

Utilities::Winapi::SmartPointer::WindowDC Window::GetDeviceContext() noexcept
{
	return { this };
}

HWND Window::GetHandle() const noexcept
{
	return m_handle;
}

Vector2i Window::GetSize() const noexcept
{
	return m_size;
}
