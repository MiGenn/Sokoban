#pragma once
#include "Window.h"

class DeviceContextWrapper final
{
public:
	DeviceContextWrapper(const Window* window);
	DeviceContextWrapper(const DeviceContextWrapper&) = delete;
	~DeviceContextWrapper();

	DeviceContextWrapper& operator=(const DeviceContextWrapper&) = delete;

	HDC Get() const;

private:
	const Window* const m_window;
	const HDC m_windowContext;
};
