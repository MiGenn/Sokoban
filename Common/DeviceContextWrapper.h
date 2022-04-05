#pragma once
#include "Window.h"

class DeviceContextWrapper final
{
public:
	DeviceContextWrapper(const Window* window) NOEXCEPT_WHEN_NDEBUG;
	DeviceContextWrapper(const DeviceContextWrapper&) = delete;
	~DeviceContextWrapper() noexcept;

	DeviceContextWrapper& operator=(const DeviceContextWrapper&) = delete;

	HDC Get() const noexcept;

private:
	const Window* const m_window;
	const HDC m_windowContext;
};
