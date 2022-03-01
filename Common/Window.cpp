#include "Window.h"
#include "DeviceContextWrapper.h"
#include <iomanip>

Window::Window(int width, int height) : 
	m_handle(nullptr)
{
	m_width = width;
	m_height = height;
}

void Window::Resize(int width, int height)
{
	if (!SetWindowPos(m_handle, nullptr, NULL, NULL, width, height, SWP_NOMOVE | SWP_NOZORDER))
		throw LAST_EXCEPTION();

	m_width = width;
	m_height = height;
}

HWND Window::GetHandle() const
{
	return m_handle;
}

DeviceContextWrapper Window::GetDeviceContext()
{
	return { this };
}

Vector2i Window::GetSize() const
{
	return { m_width, m_height };
}
